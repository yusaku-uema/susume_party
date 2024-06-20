#include "BlackMage.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BLACKMAGE_SIZE 20
#define WALK_SPEED 2.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 7.5  //上昇、下降の上限
#define SEARCH_RANGE 600 //索敵範囲
#define IMAGE_SWITCHING_TIMING 12 //画像切替タイミング
#define WAITING_TIME_FOR_ATTACK 60 //攻撃待機時間（攻撃タイミング）
#define MAX_HP 150


BlackMage::BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
{
	OutputDebugString("魔導士コンストラクタ呼ばれました。\n");


	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/blackmage.png", 14, 14, 1, 131, 132, blackmage_image) == -1)throw("魔導士（ボス）像読込み失敗\n");

	this->hp = MAX_HP;
	image_type = 0;
	animation_time = 0;
	roundtrips = 0;
	time = 0;
	num = 2;

	attack_speed = 0;
	distance_moved = 0;


	is_facing_left = true;
	direction = true;
	lock_on = false;
	attack = false;


	state = BLACKMAGE_STATE::STANDBY;

	//this->location = { 2300,330 };
	attack_location = { 0,0 };
	this->location = location;
	this->radius = { BLACKMAGE_SIZE, 40 };


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
		Attack();
		break;
	case BLACKMAGE_STATE::ATTACK_STANDBY:
		Standby();
		break;
	case BLACKMAGE_STATE::STANDBY:
		if (CalculateDistance() < SEARCH_RANGE)
		{
			state = BLACKMAGE_STATE::NORMAL;
		}
		break;
	case BLACKMAGE_STATE::TELEPORT:
		TeleportAttack();
		break;
	default:
		break;
	}

	if (hp <= 0)
	{
		is_dead = true;
	}

}

void BlackMage::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		DrawRotaGraph(draw_location.x, draw_location.y - 20, 1.5, 0, blackmage_image[image_type], TRUE, !is_facing_left);

		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x00ffff, FALSE);
		DrawHPBar(MAX_HP);

		DrawFormatString(draw_location.x, draw_location.y - 100, 0xffffff, "x%f  y%f", location.x, location.y);

		DrawBox(attack_location.x - 30, 300 - 250, attack_location.x + 30, 300 + 250, 0x00ffff, FALSE);

	}
}

void BlackMage::Move()
{

	MoveAttack();

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

	if (is_facing_left) //フラグがTRUEの間、左に動き続ける。
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
			if (is_facing_left)
			{
				location.x += speed.x;
			}
			else
			{
				location.x -= speed.x;
			}
		}
		roundtrips++;
		is_facing_left = !is_facing_left;

		if (roundtrips > num)
		{
			num = GetRand(3);
			state = BLACKMAGE_STATE::ATTACK_STANDBY;
			roundtrips = 0;
			time = 0;
			old_hp = hp;
		}
	}

}

void BlackMage::Standby()
{

	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		location.y -= speed.y;
	}

	if (old_hp - 20 < hp)
	{

	}

	if (++time % 600 == 0)
	{
		state = BLACKMAGE_STATE::ATTACK;
	}

	if (time % 60 == 0)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { 0,0 }, -1, 20, ATTACK_TYPE::EXPLOSION, 1.0f);
	}

}

void BlackMage::Wait()
{

	//location.y--;

	if (++time % 200 == 0)
	{
		state = BLACKMAGE_STATE::TELEPORT;
	}



}

void BlackMage::Attack()
{
	if (is_facing_left)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { -10,0 }, 10, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
	}
	else
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { +10,0 }, 10, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
	}

	state = BLACKMAGE_STATE::WAIT;
}

void BlackMage::MoveAttack()
{
	if (++time % 60 == 0)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 60,60 }, { 0,+10 }, 10, 5, ATTACK_TYPE::EXPLOSION, 1.0f);
	}
}

void BlackMage::TeleportAttack()
{
	location = { 8900,300 };

	if (lock_on)
	{
		if (attack)
		{
			if (++time % 600 == 0)
			{
				attack_manager->AddEnemyAttack({ attack_location.x,300 }, { 30,250 }, { 0,0 }, 3, 10, ATTACK_TYPE::EXPLOSION, 4.0f);
				attack = false;
				time = 0;
			}
		}
		else
		{
			if (++time % 300 == 0)
			{
				time = 0;
				lock_on = false;
				state = BLACKMAGE_STATE::NORMAL;
			}
		}
	}
	else
	{
		attack_location = player_manager->GetPlayerData()->GetLocation();
		lock_on = true;
		attack = true;
		attack_manager->AddEnemyAttack({ attack_location.x,500 }, { 0,0 }, { 0,0 }, 5, 0, ATTACK_TYPE::EXPLOSION, 1.0f);
	}

}

float BlackMage::CalculateDistance()
{
	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
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
