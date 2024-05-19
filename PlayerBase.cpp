#include"DxLib.h"
#include"PlayerBase.h"
#include"Key.h"

#define PLAYER_SIZE_X 30.0f//サイズ
#define PLAYER_SIZE_Y 50.0f//サイズ

#define WALK_SPEED 3.0f//1フレームで進む速さ

#define JUMP_SPEED 7.0f//1フレームでジャンプする高さ

#define ACCELERATION 0.15f//歩く時の加速

#define CHARACTER_DISTANCE 90.0f//キャラクター同士の距離

#define IMAGE_CHANGE_TIME 0.15f//画像切り替えの時間(秒数)
#define PLAYER_IMAGE_NUM 4//プレイヤー画像の種類

PlayerBase::PlayerBase(class Stage* stage, PLAYER_JOB player_job) : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 20, 10, 5, 5),
stage(stage), player_job(player_job), is_dead(false), is_facing_left(false), image_change_time(0.0f),
draw_image_num(0), is_leader(false),is_casket_fall(false)
{
    draw_image_num = GetRand(3);
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    if (LoadDivGraph("image/Player/casket.png", 5, 5, 1, 50, 50, player_image[2]) == -1)throw("image/Player/casket.pngが読み込めません\n");

    OutputDebugString("PlayerBaseコンストラクタ呼ばれました。\n");
}

PlayerBase::~PlayerBase()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)DeleteGraph(player_image[i][j]);
    }

    OutputDebugString("PlayerBaseデストラクタが呼ばれました。\n");
}

void PlayerBase::Update(float delta_time, PlayerBase* previous_player)
{
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

    //キャラクターの座標更新
    if (is_leader)UpdateLeader();
    else UpdateFollower(previous_player);

    if (location.y > SCREEN_HEIGHT)
    {
        location.y = -500.0f;
        is_dead = true;
        is_casket_fall = true;
    }
}


void PlayerBase::UpdateLeader()
{
    //攻撃
    if (Key::KeyDown(KEY_TYPE::B))stage->AddAttack(location, { 10,10 }, { 5,0 }, 5.0, 3, 0);

    //X座標の更新

    if (Key::KeyPressed(KEY_TYPE::LEFT))//左が押されてるなら左に進む
    {
        if ((speed.x -= ACCELERATION) < -WALK_SPEED) speed.x = -WALK_SPEED;
    }
    else if (Key::KeyPressed(KEY_TYPE::RIGHT))//右が押されてるなら右に進む
    {
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
    }
    else//何も押されていない時は、徐々にスピードを落とす
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
    }

    //左右どちらに進んでいるか？
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    //Y座標の更新

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
            if (Key::KeyDown(KEY_TYPE::A))
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

    SetJumpLog(is_jump);
}



void PlayerBase::UpdateFollower(PlayerBase* previous_player)
{
    //X座標の更新

    if (is_casket_fall && location.y > 0.0f - PLAYER_SIZE_Y)speed.x = 0.0f;
    else
    {
        if ((previous_player->GetLocation().x > location.x) && ((previous_player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((previous_player->GetLocation().x < location.x) && ((location.x - previous_player->GetLocation().x) > CHARACTER_DISTANCE))
        {
            if ((speed.x -= ACCELERATION) < -WALK_SPEED)speed.x = -WALK_SPEED;
        }
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
    }

    //左右どちらに進んでいるか？
    if (speed.x < 0.0f)is_facing_left = true;
    else if (speed.x > 0.0f)is_facing_left = false;


    //Y座標の更新

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

void PlayerBase::SetJumpLog(bool is_jump)
{
    for (int i = 0; i < JUMP_LOG; i++)
    {
        if (i == JUMP_LOG - 1)jump_log[i] = is_jump;
        else jump_log[i] = jump_log[i + 1];
    }
}

bool PlayerBase::GetJumpLog()const
{
    return jump_log[0];
}

bool PlayerBase::GetIsDead()const//プレイヤーが死んでいるか？
{
    return is_dead;
}

bool PlayerBase::GetIsLeader()const
{
    return is_leader;
}

PLAYER_JOB PlayerBase::GetPlayerJob()const
{
    return player_job;
}

void PlayerBase::Draw(float camera_work) const
{
    DATA draw_location = { location.x + camera_work, location.y };

    if ((draw_location.x >= -50.0f) && (draw_location.x <= SCREEN_WIDTH + 50.0f))
    {
        int draw_image_type = (speed.x == 0.0f);
        if (is_dead)draw_image_type = 2;

        DrawRotaGraph(draw_location.x, draw_location.y, 2.0, 0, player_image[draw_image_type][draw_image_num], TRUE, is_facing_left);
        //DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
    }

    //DrawFormatString(0, 500, 0xffffff, "%f", location.y);
}