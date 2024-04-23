#include"DxLib.h"
#include"Slime.h"

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//歩く時の加速

Slime::Slime() : CharacterBase({ 400.0f, 200.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
    OutputDebugString("Slimeコンストラクタ呼ばれました。\n");
}

Slime::~Slime()
{
    OutputDebugString("Slimeデストラクタが呼ばれました。\n");
}

void Slime::Update(float delta_time, Stage* stage)
{
    if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
    location.y += speed.y;

    if (stage->HitBlock(this))
    {
        //x座標の更新
        if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定
        location.x += speed.x;

        location.y -= speed.y;
    }
}

void Slime::Draw(float camera_work) const
{
    DATA draw_location = { location.x + camera_work, location.y };

    if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
    {
        DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
    }
}