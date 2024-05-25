#include "Flower.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define FLOWER_SIZE 80.0f//サイズ
#define TIMING_ATTACK 120 //攻撃タイミング
#define SEARCH_RANGE 250 //交戦距離


//-----------------------------------
//コンストラクタ
//-----------------------------------
Flower::Flower(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : CharacterBase({ 1400.0f, 50.0f }, { FLOWER_SIZE, FLOWER_SIZE }, 20, 10, 5, 5)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/flower.png", 7, 7, 1, 80, 80, flower_image) == -1)throw("フラワー画像読込み失敗\n");

	time = 0;
	animation_time = 0;
	image_type = 4;
	start_attack = false;

	direction = true;

	state = FLOWER_STATE::STANDBY;

}


//-----------------------------------
//デストラクタ
//-----------------------------------
Flower::~Flower()
{

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(flower_image[i]);
	}
}


//-----------------------------------
//更新処理
//-----------------------------------
void Flower::Update(float delta_time)
{
	//画像切替時間測定
	++time;


	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		location.y -= speed.y;
	}


	switch (state)
	{
	case FLOWER_STATE::ATTACK:
		
		Attack(delta_time);

		break;
	case FLOWER_STATE::STANDBY:

		//画像切替処理
		if (time % 12 == 0)
		{
			if (++image_type > 6)
			{
				image_type = 4;
			}
		}
		if (CalculateDistance() < SEARCH_RANGE)
		{
			state = FLOWER_STATE::ATTACK;
			image_type = 0;
		}
		break;

	default:
		break;
	}

}


//-----------------------------------
//描画
//-----------------------------------
void Flower::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, flower_image[image_type], TRUE, direction);
	}
}


//-----------------------------------
//攻撃
//-----------------------------------
void Flower::Attack(float delta_time)
{

	if (++animation_time % TIMING_ATTACK == 0)
	{
		if (direction)
		{
			//攻撃
			attack_manager->AddEnemyAttack(location, { 15,15 }, { +5,0 }, 10, 3, 1);
		}
		else
		{
			//攻撃
			attack_manager->AddEnemyAttack(location, { 15,15 }, { -5,0 }, 10, 3, 1);
		}
		image_type = 1;
	}


	if (image_type > 0)
	{
		//画像切替処理
		if (time % 12 == 0)
		{
			if (++image_type > 4)
			{
				image_type = 0;
			}
		}
	}

	//交戦距離から離れたら攻撃停止
	if (CalculateDistance() > SEARCH_RANGE)
	{
		state = FLOWER_STATE::STANDBY;
		image_type = 4;
	}


}


//-----------------------------------
//相手との距離を測る
//-----------------------------------
float Flower::CalculateDistance()
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
