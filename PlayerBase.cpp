#include"DxLib.h"
#include"PlayerBase.h"
#include"Key.h"

#define PLAYER_SIZE_X 30.0f//サイズ
#define PLAYER_SIZE_Y 60.0f//サイズ
#define WALK_SPEED 3.0f//1フレームで進む速さ
#define JUMP_SPEED 8.0f//1フレームでジャンプする高さ
#define ACCELERATION 0.15f//歩く時の加速
#define CHARACTER_DISTANCE 80.0f//キャラクター同士の距離

#define IMAGE_CHANGE_TIME 0.15f//画像切り替えの時間(秒数)
#define PLAYER_IMAGE_NUM 4//プレイヤー画像の種類

PlayerBase::PlayerBase() : CharacterBase({ 90.0f, 200.0f }, { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 20, 10, 5, 5), 
is_dead(false), is_facing_left(false), image_change_time(0.0f), draw_image_num(1)
{
    for (int i = 0; i < JUMP_LOG; i++)jump_log[i] = false;
    OutputDebugString("PlayerBaseコンストラクタ呼ばれました。\n");
}

PlayerBase::~PlayerBase()
{
    OutputDebugString("PlayerBaseデストラクタが呼ばれました。\n");
}

void PlayerBase::Update(float delta_time, class Stage* stage, PlayerBase* previous_player)
{

    if (Key::KeyDown(KEY_TYPE::B) && previous_player == nullptr)stage->AddAttack(location, { 10,10 }, { 5,0 }, 5.0, 3, 0);
    //x座標の更新
    MoveX(stage, previous_player);

    location.x += speed.x;//座標の加算
    
    if (speed.x == 0.0f)draw_image_num = 1;
    else
    {
        if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
        {
            if (++draw_image_num >= PLAYER_IMAGE_NUM)draw_image_num = 0;
            image_change_time = 0.0f;
        }
        if (speed.x < 0.0f)is_facing_left = true;//左に進んでいるならis_facing_leftをtrueにする
        else if (speed.x > 0.0f)is_facing_left = false;//右に進んでいるならis_facing_leftをfalseにする
    }
   

    if (stage->HitBlock(this))//ブロックに当たっている場合、座標を調整
    {
        location.x = roundf(location.x);//座標を整数値にする
        while (stage->HitBlock(this))location.x -= (speed.x / fabsf(speed.x));//ブロックに当たっている間、進行方向とは逆に進める
    }

    //y座標の更新
    MoveY(stage, previous_player);

    if (location.y > 600.0f)is_dead = false;
}

void PlayerBase::MoveX(class Stage* stage, PlayerBase* player)
{
    if (player == nullptr)
    {
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
    }
    else
    {
        if ((player->GetLocation().x > location.x) && ((player->GetLocation().x - location.x) > CHARACTER_DISTANCE))
        {
            if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;
        }
        else if ((player->GetLocation().x < location.x) && ((location.x - player->GetLocation().x) > CHARACTER_DISTANCE))
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
}

//y座標の更新
void PlayerBase::MoveY(class Stage* stage, PlayerBase* previous_player)
{
    bool is_jump = false;

    speed.y += GRAVITY;//重力の加算
    if (speed.y > JUMP_SPEED)speed.y = JUMP_SPEED;//重力が一定数を越えないようにする
    location.y += speed.y;//座標の加算

    if (stage->HitBlock(this))//もしブロックに当たっていたら（地面か頭に当たっている）
    {
        location.y = roundf(location.y);//座標を整数値にする
        while (stage->HitBlock(this))location.y -= (speed.y / fabsf(speed.y));//ブロックに当たっている間、進行方向とは逆に進める

        if (speed.y > 0.0f)//地面に当たっている場合
        {
            if (previous_player == nullptr)//先頭キャラがいない場合
            {
                if (Key::KeyDown(KEY_TYPE::A))
                {
                    speed.y = -JUMP_SPEED;//Aボタンでジャンプ
                    is_jump = true;
                }
                else speed.y = 0.0f;
            }
            else//先頭キャラがいる場合
            {
                if (previous_player->GetJumpLog())speed.y = -JUMP_SPEED;
                else speed.y = 0.0f; 
            } 
        }
        else speed.y = 0.0f;//頭にブロックが当たっている場合、Yのスピードを0にする
    }

    if(previous_player == nullptr)SetJumpLog(is_jump);
    else SetJumpLog(previous_player->GetJumpLog());
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

void PlayerBase::Draw(float camera_work) const
{
    DATA draw_location = { location.x + camera_work, location.y };

    if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))
    {
         DrawRotaGraph(draw_location.x, draw_location.y, 2.5, 0, player_image[draw_image_num], TRUE, is_facing_left);
         DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
    }

    //DrawFormatString(0, 500, 0xffffff, "%f", location.y);
}