#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Slime.h"

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//歩く時の加速

Slime::Slime() : CharacterBase({ 1000.0f, 300.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
    OutputDebugString("Slimeコンストラクタ呼ばれました。\n");
    if (LoadDivGraph("image/Enemy/Slime_image.png", 12, 12, 1, 48, 48, slime_image) == -1)throw("スライム画像読込み失敗\n");
    image_type = 0;
    move_left = true;
    
    time = 0;

    state = SLIME_STATE::NORMAL;
}

Slime::~Slime()
{
    OutputDebugString("Slimeデストラクタが呼ばれました。\n");
    for (int i = 0; i < 12; i++)
    {
        DeleteGraph(slime_image[i]);
    }
}

void Slime::Update(float delta_time, Stage* stage, class PlayerManager* player)
{

    switch (state)
    {
    case SLIME_STATE::NORMAL:
        Move(stage, player);
        break;
    case SLIME_STATE::ATTACK:
        Attack(stage, player, delta_time);
        break;
    }

    //画像切替処理
    if (++time % 12 == 0)
    {
        if (++image_type > 3)
        {
            image_type = 0;
        }
    }

}

void Slime::Draw(float camera_work) const
{
    DATA draw_location = { location.x + camera_work, location.y };

    if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
    {
        //DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
        DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, slime_image[image_type], TRUE, !move_left);
    }
}

void Slime::Move(Stage* stage, PlayerManager* player)
{
    if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
    location.y += speed.y;

    if (stage->HitBlock(this))
    {
        location.y -= speed.y;
    }

    //x座標の更新
    if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定

    if (move_left) //左に進行するのか
    {
        location.x -= speed.x;
    }
    else
    {
        location.x += speed.x;
    }

    if (stage->HitBlock(this))
    {
        move_left = !move_left;
    }


    if (CalculateDistance(player) < 60)
    {
        state = SLIME_STATE::ATTACK;
    }

}

void Slime::Attack(Stage* stage, PlayerManager* player, float delta_time)
{
    //当たり判定の処理を書く



    if (CalculateDistance(player) > 60|| stage->HitBlock(this))
    {
        state = SLIME_STATE::NORMAL;
    }

}

float Slime::CalculateDistance(PlayerManager* player)
{
    float dx = player->GetPlayerLocation().x - this->GetLocation().x;
    float dy = player->GetPlayerLocation().y - this->GetLocation().y;
    float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）
    // プレイヤーと敵の座標から角度を計算
    float angle = atan2(dy, dx) * 180 / M_PI;

    if (move_left)
    {
        if (angle >= -180 && angle <= -3) {
            return distance; // プレイヤーが正面にいる
        }
   }
    else
    {
        if (angle >= -45 && angle <= 45) {
            return distance; // プレイヤーが正面にいる
        }
    }
     return 999; // プレイヤーが正面にいないか、索敵範囲外
}
