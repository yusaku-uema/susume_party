#include"DxLib.h"
#include"PlayerBase.h"
#include"Stage.h"
#include"Key.h"

#define PI 3.14159265358979323846// pi

#define PLAYER_SIZE_X 30.0f//サイズ
#define PLAYER_SIZE_Y 50.0f//サイズ

#define ACCELERATION 0.15f//歩く時の加速
#define WALK_SPEED 3.0f//1フレームで進む速さ
#define JUMP_SPEED 7.0f//1フレームでジャンプする高さ
#define CHARACTER_DISTANCE 90.0f//キャラクター同士の距離

#define IMAGE_CHANGE_TIME 0.15f//画像切り替えの時間(秒数)
#define PLAYER_IMAGE_NUM 4//プレイヤー画像の種類

#define MAX_WEAPON_ANGLE 360

PlayerBase::PlayerBase(DATA location,int hp,int mp, int attack_power, PLAYER_JOB player_job) : CombatCharacterBase(location, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, hp, mp, attack_power, 5),
player_job(player_job), weapon_angle(0),
is_leader(false), is_casket_fall(false), is_party_member(true), is_set_casket(false)
{
    max_hp = hp;
    max_mp = mp;

    //ジャンプの記録をリセット
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;

    is_facing_left = true;

    if (LoadDivGraph("image/Player/casket.png", 5, 5, 1, 50, 50, player_image[2]) == -1)throw("image/Player/casket.pngが読み込めません\n");

    OutputDebugString("PlayerBaseコンストラクタ呼ばれました。\n");
}

PlayerBase::~PlayerBase()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)DeleteGraph(player_image[i][j]);
    }

    DeleteGraph(weapon_image);

    OutputDebugString("PlayerBaseデストラクタが呼ばれました。\n");
}


bool PlayerBase::Update(float delta_time, PlayerBase* previous_player)
{
    //キャラが先頭か？
    if (previous_player == nullptr)is_leader = true;
    else is_leader = false;

    //プレイヤー画像の切り替え
    if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
    {
        if (!is_dead || speed.x != 0.0f)
        {
            if (++draw_image_num >= PLAYER_IMAGE_NUM)draw_image_num = 0;
        }
        image_change_time = 0.0f;
    }

    if (weapon_angle != 0)
    {
        if ((weapon_angle += 15) > MAX_WEAPON_ANGLE)weapon_angle = 0;
    }

    //キャラクターの座標更新
    if (is_leader)
    {
        //先頭キャラの場合
        UpdateLeader();
    }
    else
    {
        //先頭キャラ以外の場合
        UpdateFollower(previous_player);
    }

    //キャラが死んだ場合
    if (location.y > SCREEN_SIZE_Y)is_set_casket = true;
    else if ((location.x > stage->GetCenterLocationX() + 800.0f) || (location.x < stage->GetCenterLocationX() - 800.0f))is_set_casket = true;

    if(is_set_casket)
    {
        //先頭キャラの真上に落とす
        location.x = player_manager->GetPlayerData()->GetLocation().x;
        location.y = -400.f;

        //落ちている状態にする
        is_casket_fall = true;

        //死亡状態にする
        is_dead = true;
        
        //hpを0にする
        hp = 0;

        //棺桶にするかのフラグをfalseにする
        is_set_casket = false;

        return true;
    }

    return false;
}


////先頭キャラの更新//////

void PlayerBase::UpdateLeader()
{
    if((weapon_angle == 0) && (!player_manager->GetiIsTalking()))
    {
        if (Key::KeyDown(KEY_TYPE::B))//物理攻撃(Bボタン入力時)
        {
            //左に攻撃
            if (is_facing_left) attack_manager->AddPlayerAttack({ location.x - 50.0f, location.y }, { 40.0f,40.0f }, { 0.0f,0.0f }, nullptr,false,true, -1.0f, 3, ATTACK_TYPE::SLASHING, 0.0f);
            //右に攻撃
            else attack_manager->AddPlayerAttack({ location.x + 50.0f, location.y }, { 40.0f,40.0f }, { 0.0f,0.0f }, nullptr,false,true, -1.0f, 3, ATTACK_TYPE::SLASHING, 0.0f);

            weapon_angle += 15;
        }
        else if (Key::KeyDown(KEY_TYPE::Y))//攻撃2(Yボタン入力時)
        {
            SpecialSkill();
            weapon_angle += 15;
        }
    }

    //////X座標の更新////////


    //左右キー入力された場合、その方向に進める

    if ((Key::KeyPressed(KEY_TYPE::LEFT)) && (!player_manager->GetiIsTalking()))
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if ((Key::KeyPressed(KEY_TYPE::RIGHT)) && (!player_manager->GetiIsTalking()))
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }

    //左右キーが入力されていない場合、徐々にスピードを落とす
    else
    {
        if (speed.x < 0.0f)
        {
            if ((speed.x += ACCELERATION) > 0.0f) speed.x = 0.0f;
        }
        else if (speed.x > 0.0f)
        {
            if ((speed.x -= ACCELERATION) < 0.0f)speed.x = 0.0f;
        }
    }

    //座標の加算
    location.x += speed.x;

    //ブロックに当たっている場合
    if (stage->HitBlock(this))
    {
        //座標を調整
        location.x = roundf(location.x);
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));
        speed.x = 0.0f;
    }

    //左右どちらに進んでいるか？
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    /////Y座標の更新/////////////


    //ジャンプしたか？
    bool is_jump = false;

    //重力の加算
    if((speed.y += GRAVITY) > JUMP_SPEED)speed.y = JUMP_SPEED;

    //座標の加算
    location.y += speed.y;

    //ブロックに当たった場合
    if (stage->HitBlock(this))
    {
        //座標の調整
        location.y = roundf(location.y);
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));

        //地面に当たっている場合
        if (speed.y > 0.0f)
        {
            if ((Key::KeyDown(KEY_TYPE::A)) && (!player_manager->GetiIsTalking()))
            {
                speed.y = -JUMP_SPEED;//Aボタンでジャンプ
                is_jump = true;
            }
            else speed.y = 0.0f;
        }
        else
        {
            speed.y = 0.0f;//頭にブロックが当たっている場合、Yのスピードを0にする
            draw_image_num = 4;
        }
    }
    else draw_image_num = 4;

    //ジャンプしたことを記録する
    if(is_party_member)SetJumpLog(is_jump);
}


///先頭キャラ以外の更新/////////

void PlayerBase::UpdateFollower(PlayerBase* previous_player)
{
    ////X座標の更新////////

    //棺桶で空から降ってくる
    if (is_casket_fall)
    {
        //x座標は動かさない
        speed.x = 0.0f;
    }

    //棺桶じゃないとき
    else
    {
        //パーティ状態で、前のキャラと離れていたら動く
        if ((is_party_member) && (previous_player->GetLocation().x > location.x) && ((previous_player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((is_party_member) && (previous_player->GetLocation().x < location.x) && ((location.x - previous_player->GetLocation().x) > CHARACTER_DISTANCE))
        {
            if ((speed.x -= ACCELERATION) < -WALK_SPEED)speed.x = -WALK_SPEED;
        }

        //徐々に止まる
        else
        {
            if (speed.x < 0.0f)
            {
                if ((speed.x += ACCELERATION) > 0.0f) speed.x = 0.0f;
            }
            else if (speed.x > 0.0f)
            {
                if ((speed.x -= ACCELERATION) < 0.0f)speed.x = 0.0f;
            }
        }
    }

    //座標の加算
    location.x += speed.x;

    //ブロックに当たっている場合
    if (stage->HitBlock(this))
    {
        //座標を調整
        location.x = roundf(location.x);
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));
        speed.x = 0.0f;
    }

    //左右どちらに進んでいるか？
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    ////Y座標の更新/////////////////

    //ジャンプしたか？
    bool is_jump = false;

    //重力の加算
    if (is_casket_fall)speed.y = JUMP_SPEED * 1.5;
    else if ((speed.y += GRAVITY) > JUMP_SPEED)speed.y = JUMP_SPEED;

    //座標の加算
    location.y += speed.y;

    //ブロックに当たった場合
    if (stage->HitBlock(this))
    {
        //座標の調整
        location.y = roundf(location.y);
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));

        //地面に当たっている場合
        if (speed.y > 0.0f)
        {
            if (is_casket_fall)is_casket_fall = false;

            if (previous_player->GetJumpLog())speed.y = -JUMP_SPEED;
            else speed.y = 0.0f;
        }
        else
        {
            speed.y = 0.0f;//頭にブロックが当たっている場合、Yのスピードを0にする
            draw_image_num = 4;
        }
    }
    else draw_image_num = 4;

    SetJumpLog(previous_player->GetJumpLog());
}

//ダメージが当たった時
bool PlayerBase::HitDamege(BoxCollider* bc, int attack_power)
{
    if (!is_dead)
    {
        if ((hp -= attack_power) <= 0)
        {
            hp = 0;
            attack_manager->AddPlayerAttack(location, { 0.0f,0.0f }, { 0.0f,0.0f }, nullptr,false,false, -1.0f, 0, ATTACK_TYPE::SMALL_EXPLOSION, 5.0f);
            is_set_casket = true;
            
        }
        else if (location.x > bc->GetLocation().x)speed.x = 5.0f;
        else speed.x = -5.0f;
    }
    return is_dead;
}

void PlayerBase::SetJumpLog(bool is_jump)
{
    for (int i = 0; i < JUMP_LOG; i++)
    {
        if (i == JUMP_LOG - 1)jump_log[i] = is_jump;
        else jump_log[i] = jump_log[i + 1];
    }
}

void PlayerBase::SetIsPartyMember(bool is_party_member)
{
    if (this->is_party_member != is_party_member)
    {
        this->is_party_member = is_party_member;
        for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    }
}

bool PlayerBase::GetIsPartyMember()const
{
    return is_party_member;
}

bool PlayerBase::GetJumpLog()const
{
    return jump_log[0];
}

bool PlayerBase::GetIsLeader()const
{
    return is_leader;
}

PLAYER_JOB PlayerBase::GetPlayerJob()const
{
    return player_job;
}

void PlayerBase::Draw() const
{
    DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

    int draw_image_type = (speed.x == 0.0f); //歩いているときの画像
    if (is_dead)draw_image_type = 2;

    //プレイヤー表示
    DrawRotaGraph(draw_location.x, draw_location.y, 2.0, 0, player_image[draw_image_type][draw_image_num], TRUE, is_facing_left);

    if (!is_dead)
    {
        DATA weapon_location = { -10.0f, 5.0f };//武器の座標
        DATA weapon_center = { 25.0f, 25.0f };//武器の中心点

        weapon_location.y += draw_image_num;
        int weapon_angle = this->weapon_angle;

        if (is_facing_left)
        {
            weapon_location.x = -weapon_location.x;
            weapon_center.x = 7.0f;
            weapon_angle = -weapon_angle;
        }

        //武器表示
        DrawRotaGraph2(draw_location.x + weapon_location.x, draw_location.y + weapon_location.y, weapon_center.x, weapon_center.y, 2.0, (PI / 180) * weapon_angle, weapon_image, TRUE, is_facing_left);
        //DrawCircle(draw_location.x + weapon_location.x, draw_location.y + weapon_location.y, 2, 0xf00ff0, TRUE);
    }

    //DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);

    //DrawRotaGraph(stage->GetCameraWork() + (), 500, 1, 0, player_image[0][0], TRUE);
    //DrawFormatString(0, 500, 0xffffff, "%f", (-stage->GetCameraWork() + 600));
}