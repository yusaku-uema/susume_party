#include "Flower.h"
#include"DxLib.h"

#define MAX_HP 500

#define FLOWER_SIZE_X 10.0f//サイズ
#define FLOWER_SIZE_Y 60.0f//サイズ


#define SEARCH_RANGE 250.0f //交戦距離
#define PREPARING_ATTACK_TIME 1.0f //攻撃溜め時間
#define ATTACK_INTERVAL_TIME 7.0f //攻撃間隔

#define IMAGE_CHANGE_TIME 0.2f //画像切り替え時間


//-----------------------------------
//コンストラクタ
//-----------------------------------
Flower::Flower(DATA location, class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : EnemyBase(location, { FLOWER_SIZE_X , FLOWER_SIZE_Y}, MAX_HP, 5, 5)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	enemy_control_time = ATTACK_INTERVAL_TIME;

	//画像
	if (LoadDivGraph("image/Enemy/flower/normal.png", 3, 3, 1, 80, 80, enemy_image[ENEMY_STATE::NORMAL]) == -1)throw("image/Enemy/flower/normal.png\n");
	if (LoadDivGraph("image/Enemy/flower/preparingattack.png", 1, 1, 1, 80, 80, enemy_image[ENEMY_STATE::PREPARING_ATTACK]) == -1)throw("image/Enemy/flower/preparingattack.png\n");
	if (LoadDivGraph("image/Enemy/flower/attack.png", 3, 3, 1, 80, 80, enemy_image[ENEMY_STATE::ATTACK]) == -1)throw("image/Enemy/flower/attack.png\n");
}


//-----------------------------------
//デストラクタ
//-----------------------------------
Flower::~Flower()
{
}


//-----------------------------------
//更新処理
//-----------------------------------
void Flower::Update(float delta_time)
{
	//Y座標更新

	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;

	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		location.y -= speed.y;
		speed.y = 0.0f;
	}
	
	//状態ごとの処理

	enemy_control_time += delta_time;

	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
	{
		draw_image_num++;
		image_change_time = 0.0f;
	}

	switch (enemy_state)
	{
	case ENEMY_STATE::NORMAL:

		if (enemy_image[ENEMY_STATE::NORMAL][draw_image_num] == NULL)draw_image_num = 0;

		is_facing_left = (location.x > player_manager->GetPlayerData()->GetLocation().x);

		if (enemy_control_time > 7.0f)
		{
			if (CalculateDistance(player_manager->GetPlayerData()) < SEARCH_RANGE)
			{
				ChangeEnemyState(ENEMY_STATE::PREPARING_ATTACK);
			}
		}

		break;

	case ENEMY_STATE::PREPARING_ATTACK:

		if (enemy_image[ENEMY_STATE::PREPARING_ATTACK][draw_image_num] == NULL)draw_image_num = 0;

		if (enemy_control_time > PREPARING_ATTACK_TIME)
		{
			//攻撃
			if (is_facing_left)attack_manager->AddEnemyAttack({location.x - 10.0f, location.y}, {15.0f,15.0f}, {-5.0f,0.0f}, 10.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
			else attack_manager->AddEnemyAttack({ location.x + 10.0f, location.y }, { 15.0f,15.0f }, { 5.0f,0.0f }, 10.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);

			ChangeEnemyState(ENEMY_STATE::ATTACK);
		}

		break;

	case ENEMY_STATE::ATTACK:

		if (enemy_image[ENEMY_STATE::ATTACK][draw_image_num] == NULL)ChangeEnemyState(ENEMY_STATE::NORMAL);

		break;

	default:
		break;
	}

	hp--;
}

//-----------------------------------
//描画
//-----------------------------------
void Flower::Draw(DATA draw_location) const
{
	DrawRotaGraph(draw_location.x, draw_location.y - 10.0f, 1, 0, enemy_image[enemy_state][draw_image_num], TRUE, !is_facing_left);

	//DrawFormatString(draw_location.x ,draw_location.y-200,0xffffff, "HP = %d", hp);
	DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
	//DrawFormatString(draw_location.x, draw_location.y - 100, 0xffffff, "向く方向%f", angle);
}
