#include "Flower.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define FLOWER_SIZE 80.0f//サイズ
#define TIMING_ATTACK 120 //攻撃タイミング
#define SEARCH_RANGE 250 //交戦距離


Flower::Flower() : CharacterBase({ 1400.0f, 50.0f }, { FLOWER_SIZE, FLOWER_SIZE }, 20, 10, 5, 5)
{
	if (LoadDivGraph("image/Enemy/flower.png", 7, 7, 1, 80, 80, flower_image) == -1)throw("フラワー画像読込み失敗\n");

	time = 0;
	animation_time = 0;
	image_type = 4;
	start_attack = false;

	direction = true;

	state = FLOWER_STATE::STANDBY;

}

Flower::~Flower()
{

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(flower_image[i]);
	}
}

void Flower::Update(float delta_time, Stage* stage, PlayerManager* player)
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
		
		Attack(stage, player, delta_time);

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
		if (CalculateDistance(player) < SEARCH_RANGE)
		{
			state = FLOWER_STATE::ATTACK;
			image_type = 0;
		}
		break;

	default:
		break;
	}

}

void Flower::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, flower_image[image_type], TRUE, direction);
	}
}

void Flower::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

	if (++animation_time % TIMING_ATTACK == 0)
	{
		if (direction)
		{
			//攻撃
			stage->AddAttack(location, { 15,15 }, { +5,0 }, 10, 3, 1);
		}
		else
		{
			//攻撃
			stage->AddAttack(location, { 15,15 }, { -5,0 }, 10, 3, 1);
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
	if (CalculateDistance(player) > SEARCH_RANGE)
	{
		state = FLOWER_STATE::STANDBY;
		image_type = 4;
	}


}


float Flower::CalculateDistance(PlayerManager* player)
{
	float dx = player->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player->GetPlayerLocation().y - this->GetLocation().y;
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
