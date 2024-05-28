#include "BlackMage.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BLACKMAGE_SIZE 132
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 7.5  //上昇、下降の上限
#define SEARCH_RANGE 300 //交戦距離
#define IMAGE_SWITCHING_TIMING 12 //画像切替タイミング
#define WAITING_TIME_FOR_ATTACK 60 //攻撃待機時間（攻撃タイミング）


BlackMage::BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : EnemyBase()
{
	OutputDebugString("魔導士コンストラクタ呼ばれました。\n");


	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/blackmage.png", 14, 14, 1, 131, 132, blackmage_image) == -1)throw("魔導士（ボス）像読込み失敗\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	move_left = true;
	direction = true;
	lock_on = false;


	state = BLACKMAGE_STATE::WAIT;

	//テスト 座標
	this->location = { 1000,400 };


}

BlackMage::~BlackMage()
{
	OutputDebugString("ボス（黒魔導士）デストラクタが呼ばれました。\n");
	for (int i = 0; i < 14; i++)
	{
		DeleteGraph(blackmage_image[i]);
	}
}

void BlackMage::Update()
{

	//アニメーション時間更新
	++animation_time;


	switch (state)
	{
	case BLACKMAGE_STATE::WAIT:
		Wait(); //プレイヤーを見つけるまで何もしないニート
		break;
	case BLACKMAGE_STATE::NORMAL:
		Move(); //動き
		break;
	case BLACKMAGE_STATE::ATTACK:

		break;
	case BLACKMAGE_STATE::ATTACK_STANDBY:

		break;
	case BLACKMAGE_STATE::STANDBY:

		break;
	default:
		break;
	}
}

void BlackMage::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{


		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, blackmage_image[image_type], TRUE, !move_left);


	}
}

void BlackMage::Move()
{
	//画像切替処理
	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
	{
		if (++image_type > 5)
		{
			image_type = 0;
		}
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

}

void BlackMage::Standby()
{

}

void BlackMage::Wait()
{
	//先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃準備
	if (CalculateDistance() < SEARCH_RANGE)
	{
		state = BLACKMAGE_STATE::NORMAL;
	}
}

void BlackMage::Attack()
{

}

float BlackMage::CalculateDistance()
{
	return 0.0f;
}
