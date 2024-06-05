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
Fairy::Fairy(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : EnemyBase()
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	OutputDebugString("妖精コンストラクタ呼ばれました。\n");

	if (LoadDivGraph("image/Enemy/fairy.png", 12, 12, 1, 64, 64, fairy_image) == -1)throw("妖精画像読込み失敗\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	move_left = true;
	direction = true;
	lock_on = false;


	state = FAIRY_STATE::NORMAL;

	//テスト 座標
	this->location = { 1400.0f, 250.0f };
	this->radius = { FAIRY_SIZE ,FAIRY_SIZE };
	this->hp = 100;

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
void Fairy::Update()
{
	//アニメーション時間更新
	++animation_time;

	switch (state)
	{
	case FAIRY_STATE::NORMAL:
		Move();
		break;
	case FAIRY_STATE::ATTACK:
		Attack();		
		break;
	case FAIRY_STATE::STANDBY:
		Standby();
		break;
	default:
		break;
	}
}


//-----------------------------------
//描画
//-----------------------------------
void Fairy::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};

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
void Fairy::Move()
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

	//先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃準備
	if (CalculateDistance() < SEARCH_RANGE)
	{
		state = FAIRY_STATE::STANDBY;
	}

	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
	{
		if (++image_type > 3)
		{
			image_type = 0;
		}
	}


}


//-----------------------------------
//待機
//-----------------------------------
void Fairy::Standby()
{
	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
	{
		if (++image_type > 12)
		{
			image_type = 8;
		}
	}


	//先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃開始
	if (CalculateDistance() < SEARCH_RANGE)
	{
		if (++time % WAITING_TIME_FOR_ATTACK == 0)
		{
			state = FAIRY_STATE::ATTACK;
			player_location = player_manager->GetPlayerLocation();
			time = 0;
		}
	}
	else //距離が離れたら通常移動へ
	{
		state = FAIRY_STATE::NORMAL;
		time = 0;
	}

}


//-----------------------------------
//攻撃
//-----------------------------------
void Fairy::Attack()
{
	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
	{
		if (++image_type > 7)
		{
			image_type = 4;
		}

		if (image_type == 6)
		{
			float dx = player_location.x - location.x;
			float dy = player_location.y - location.y;
			float distance = sqrtf(dx * dx + dy * dy);


			if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定

			if (distance >= 5)
			{
				location.x += (dx / distance) * attack_speed;
				location.y += (dy / distance) * attack_speed;
			}
			else
			{
				attack_speed = 0;
				state = FAIRY_STATE::NORMAL;
			}

			//攻撃
			attack_manager->AddEnemyAttack(location, { 15,15 }, { (dx / distance) * 2.5f ,(dy / distance) * 2.5f }, 10, 3, BIG_EXPLOSION, 1.0f);

			state = FAIRY_STATE::NORMAL;
		}
	}

	
}


//-----------------------------------
//相手との距離を測る
//-----------------------------------
float Fairy::CalculateDistance()
{
	float dx = player_manager->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player_manager->GetPlayerLocation().y - this->GetLocation().y;
	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

	float angle = atan2(dy, dx) * 180 / M_PI;

	if (angle >= -45 && angle <= 85)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}

	return distance;
}
