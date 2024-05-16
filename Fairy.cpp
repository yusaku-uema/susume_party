#include "Fairy.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>


#define FAIRY_SIZE 64
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 7.5  //上昇、下降の上限
#define SEARCH_RANGE 300 //交戦距離
#define IMAGE_SWITCHING_TIMING 12 //画像切替タイミング
#define WAITING_TIME_FOR_ATTACK 60 //攻撃待機時間（攻撃タイミング）


//-----------------------------------
//コンストラクタ
//-----------------------------------
Fairy::Fairy() : CharacterBase({ 1400.0f, 50.0f }, { FAIRY_SIZE, FAIRY_SIZE }, 20, 10, 5, 5)
{

	OutputDebugString("妖精コンストラクタ呼ばれました。\n");

	if (LoadDivGraph("image/Enemy/fairy.png", 12, 12, 1, 64, 64, fairy_image) == -1)throw("妖精画像読込み失敗\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	start_attack = false;
	standby_attack = false;
	move_left = true;
	direction = true;
	lock_on = false;


	state = FAIRY_STATE::NORMAL;

}


//-----------------------------------
//デストラクタ
//-----------------------------------
Fairy::~Fairy()
{
	OutputDebugString("妖精デストラクタが呼ばれました。\n");
	for (int  i = 0; i < 12; i++)
	{
		DeleteGraph(fairy_image[i]);
	}
}


//-----------------------------------
//更新処理
//-----------------------------------
void Fairy::Update(float delta_time, Stage* stage, PlayerManager* player)
{
	switch (state)
	{
	case FAIRY_STATE::NORMAL:
		Move(stage, player);
		break;
	case FAIRY_STATE::ATTACK:

		break;
	case FAIRY_STATE::STANDBY:

		break;
	default:
		break;
	}
}


//-----------------------------------
//描画
//-----------------------------------
void Fairy::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{

		if (state == FAIRY_STATE::STANDBY || state == FAIRY_STATE::ATTACK)
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, fairy_image[image_type], TRUE, direction);
		}
		else
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, fairy_image[image_type], TRUE, !move_left);
		}

	}
}


//-----------------------------------
//移動
//-----------------------------------
void Fairy::Move(Stage* stage, PlayerManager* player)
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

	////先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃準備
	//if (CalculateDistance(player) < SEARCH_RANGE)
	//{
	//	standby_attack = true;
	//	state = BIRD_STATE::STANDBY;
	//	image_type = 7;
	//}


}


//-----------------------------------
//待機
//-----------------------------------
void Fairy::Standby(PlayerManager* player)
{

}


//-----------------------------------
//攻撃
//-----------------------------------
void Fairy::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

}


//-----------------------------------
//相手との距離を測る
//-----------------------------------
float Fairy::CalculateDistance(PlayerManager* player)
{
	return 0.0f;
}
