#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include"Slime.h"

#define SLIME_SIZE 10.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//歩く時の加速
#define ATTACK_DISTANCE 35// 攻撃に移る距離
#define MAX_HP 20


//-----------------------------------
//コンストラクタ
//-----------------------------------
Slime::Slime(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/Slime.png", 12, 12, 1, 48, 48, slime_image) == -1)throw("スライム画像読込み失敗\n");
	image_type = 0;
	move_left = true;
	direction = true;
	distance = 0;

	time = 0;

	state = SLIME_STATE::NORMAL;

	////テスト 座標
	//this->location = { 600.0f, 300.0f };
	this->location = location;
	this->spawn_location = location;
	this->radius = { SLIME_SIZE+20 ,SLIME_SIZE };
	this->hp = MAX_HP;
	this->is_dead = false;

	OutputDebugString("Slimeコンストラクタ呼ばれました。\n");
}


//-----------------------------------
//デストラクタ
//-----------------------------------
Slime::~Slime()
{
	OutputDebugString("Slimeデストラクタが呼ばれました。\n");

	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(slime_image[i]);
	}
}


//-----------------------------------
//更新処理
//-----------------------------------
void Slime::Update()
{
	++animation_time; //アニメーション時間更新


	if (ScopeoOfActivity(stage->GetCameraWork()))
	{
		move_left = !move_left;
	}

	switch (state)
	{
	case SLIME_STATE::NORMAL:
		Move();
		break;
	case SLIME_STATE::ATTACK:
		Attack();
		break;
	case SLIME_STATE::STANDBY:
		Standby();
		break;
	case SLIME_STATE::DEATH:
		//画像切替処理
		if (animation_time % 12 == 0)
		{
			if (++image_type > 3)
			{
				is_dead = true;
			}
		}
		break;
	}
	

	if (death_animation == false)
	{
		if (hp <= 0)
		{
			state = SLIME_STATE::DEATH;
			death_animation = true;
			image_type = 0;
		}
	}

	if (location.y > 720)
	{
		is_dead = true;
	}


}


//-----------------------------------
//描画処理
//-----------------------------------
void Slime::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		if (state == SLIME_STATE::DEATH)
		{
			DrawRotaGraph(draw_location.x, draw_location.y, ENEMY_EXPLOSION_SIZE, 0, death_effects[image_type], TRUE);
		}
		else
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, slime_image[image_type], TRUE, !move_left);
		}

		DrawHPBar(MAX_HP);

	}
}


//-----------------------------------
//移動
//-----------------------------------
void Slime::Move()
{

	//画像切替処理
	if (animation_time % 12 == 0)
	{
		if (++image_type > 3)
		{
			image_type = 0;
		}
	}

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


	if (CalculateDistance() < ATTACK_DISTANCE)
	{
		state = SLIME_STATE::ATTACK;
	}

}


//-----------------------------------
//攻撃
//-----------------------------------
void Slime::Attack()
{
	//当たり判定の処理を書く
	//画像切替処理
	if (animation_time % 12 == 0)
	{
		if (++image_type > 8)
		{
			if (player_manager->CheckHitDamage(this, 10))
			{
				state = SLIME_STATE::STANDBY;
			}
			image_type = 4;
		}
	}

	if (CalculateDistance() > ATTACK_DISTANCE || stage->HitBlock(this))
	{
		state = SLIME_STATE::NORMAL;
	}

}

void Slime::Standby()
{
	if (animation_time % 12 == 0)
	{
		if (++image_type > 11)
		{
			image_type = 9;
		}
	}

	if (++time % 120 == 0)
	{
		state = SLIME_STATE::NORMAL;
	}
}


//-----------------------------------
//相手との距離を測る
//-----------------------------------
float Slime::CalculateDistance()
{

	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
	 distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

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
