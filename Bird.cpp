#include"DxLib.h"
#include "Bird.h"

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 5  //上昇、下降の上限

Bird::Bird() : CharacterBase({ 900.0f, 50.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Birdコンストラクタ呼ばれました。\n");

	distance_moved = 0;

	move_up = false;
	move_left = true;
	fly = true;

}

Bird::~Bird()
{
	OutputDebugString("Birdデストラクタが呼ばれました。\n");
}

void Bird::Update(float delta_time, Stage* stage)
{

	//x座標の更新
	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定

	if (move_left) //フラグがTRUEの間、左に動き続ける。
	{
		location.x -= speed.x;
	}
	else
	{
		location.x += speed.x;
	}

	if (stage->HitBlock(this))
	{
		fly = false;//壁に当たった場合、飛べなくなって落ちる

		while (stage->HitBlock(this)) //進行方向とは逆に進み当たり判定から脱出
		{
			if (move_left) 
			{
				location.x += speed.x;
			}
			else
			{
				location.x -= speed.x;
			}
		}

		move_left = !move_left;
	}


	//y座標の更新
		if (fly)
		{
			if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;//スピードに加速度を足していって、最大値に達したら固定
			if ((distance_moved += UP_SPEED) > FALL_MAX)distance_moved = 0, move_up = !move_up, speed.y = 0; //初期化

			if (move_up) //フラグがTRUEの場合、上昇する
			{
				location.y -= speed.y;
			}
			else
			{
				location.y += speed.y;
			}
			if (stage->HitBlock(this))fly = false;
		}
		else
		{
			if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
			location.y += speed.y;
			if (stage->HitBlock(this))location.y -= speed.y;//地面に当たっている場合、上記の計算を相殺する。
		}

}

void Bird::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
	}
}