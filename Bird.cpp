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

}

Bird::~Bird()
{
	OutputDebugString("Birdデストラクタが呼ばれました。\n");
}

void Bird::Update(float delta_time, Stage* stage)
{
	//y座標の更新
	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;//スピードに加速度を足していって、最大値に達したら固定
	
	if ((distance_moved += UP_SPEED) > FALL_MAX)distance_moved=0, move_up = !move_up, speed.y=0; //初期化

	if (move_up) //フラグがTRUEの場合、上昇する
	{
		location.y -= speed.y;
	}
	else
	{
		location.y += speed.y;
	}
	

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




}

void Bird::Draw() const
{
	DrawBox(location.x - radius.x, location.y - radius.y, location.x + radius.x, location.y + radius.y, 0x00ffff, TRUE);
}