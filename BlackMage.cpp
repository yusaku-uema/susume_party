//#include "BlackMage.h"
//#include"DxLib.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//#define BLACKMAGE_SIZE 20
//#define WALK_SPEED 2.5f//1フレームの最大速
//#define ACCELERATION 0.1f//移動時の加速
//#define UP_SPEED 0.1f //上昇、下降の速度
//#define FALL_MAX 7.5  //上昇、下降の上限
//#define SEARCH_RANGE 600 //索敵範囲
//#define IMAGE_SWITCHING_TIMING 12 //画像切替タイミング
//#define WAITING_TIME_FOR_ATTACK 60 //攻撃待機時間（攻撃タイミング）
//#define MAX_HP 150
//
//
//BlackMage::BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
//{
//	OutputDebugString("魔導士コンストラクタ呼ばれました。\n");
//
//
//	this->stage = stage;
//	this->player_manager = player_manager;
//	this->attack_manager = attack_manager;
//
//	if (LoadDivGraph("image/Enemy/blackmage.png", 14, 14, 1, 131, 132, blackmage_image) == -1)throw("魔導士（ボス）像読込み失敗\n");
//	if (LoadDivGraph("image/Enemy/Attackeffect/tentacle attack.png", 10, 5, 2, 120, 120, tentacle_image) == -1)throw("触手攻撃読込み失敗\n");
//	if (LoadDivGraph("image/Enemy/Attackeffect/warning.png", 10, 10, 1, 120, 120, lock_image) == -1)throw("ロック画像読込み失敗\n");
//	if (LoadDivGraph("image/Enemy/Attackeffect/charge.png", 10, 5, 2, 192, 192, charge_image) == -1)throw("チャージ画像読込み失敗\n");
//
//
//	this->hp = MAX_HP;
//	image_type = 0;
//	animation_time = 0;
//	roundtrips = 0;
//	time = 0;
//	num = 2;
//
//	attack_speed = 0;
//	distance_moved = 0;
//
//
//	is_facing_left = true;
//	direction = true;
//	lock_on = false;
//	attack = false;
//	start_animation = false;
//	animation_type = 0;
//
//
//	state = BLACKMAGE_STATE::STANDBY;
//
//	//this->location = { 2300,330 };
//	attack_location = { 0,0 };
//	this->location = location;
//	this->radius = { BLACKMAGE_SIZE, 40 };
//	location.y = 300;
//
//}
//
//BlackMage::~BlackMage()
//{
//	OutputDebugString("ボス（黒魔導士）デストラクタが呼ばれました。\n");
//	for (int i = 0; i < 14; i++)
//	{
//		DeleteGraph(blackmage_image[i]);
//	}
//
//
//	for (int i = 0; i < 10; i++)
//	{
//		DeleteGraph(tentacle_image[i]);
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		DeleteGraph(lock_image[i]);
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		DeleteGraph(charge_image[i]);
//	}
//
//
//}
//
//void BlackMage::Update()
//{
//
//	//アニメーション時間更新
//	++animation_time;
//
//
//	switch (state)
//	{
//	case BLACKMAGE_STATE::WAIT:
//		Wait(); //プレイヤーを見つけるまで何もしないニート
//		break;
//	case BLACKMAGE_STATE::NORMAL:
//		Move(); //動き
//		break;
//	case BLACKMAGE_STATE::ATTACK:
//		Attack();
//		break;
//	case BLACKMAGE_STATE::ATTACK_STANDBY:
//		Standby();
//		break;
//	case BLACKMAGE_STATE::STANDBY:
//		if (CalculateDistance() < SEARCH_RANGE)
//		{
//			state = BLACKMAGE_STATE::NORMAL;
//		}
//		break;
//	case BLACKMAGE_STATE::TELEPORT:
//		TeleportAttack();
//		break;
//	default:
//		break;
//	}
//
//	if (hp <= 0)
//	{
//		is_dead = true;
//		dead_boss = true;
//	}
//
//}
//
//void BlackMage::Draw() const
//{
//	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };
//	
//
//	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))//画面内にブロックがある場合
//	{
//		DrawRotaGraph(draw_location.x, draw_location.y - 20, 1.5, 0, blackmage_image[image_type], TRUE, !is_facing_left);
//		DrawHPBar(MAX_HP);
//
//		
//		if (state == BLACKMAGE_STATE::ATTACK_STANDBY)
//		{
//			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, charge_image[animation_type], TRUE);
//		}
//		
//		if (state == BLACKMAGE_STATE::TELEPORT)
//		{
//			DATA draw_location = { attack_location.x + stage->GetCameraWork(), location.y };
//			
//			DrawRotaGraph(draw_location.x, 430, 1, 0, lock_image[animation_type], TRUE);
//			
//			if (start_animation)
//			{
//				
//				DrawRotaGraph(draw_location.x, 350, 2, 0, tentacle_image[animation_type], TRUE);
//			}
//		}
//	}
//}
//
//void BlackMage::Move()
//{
//
//	MoveAttack();
//
//	//画像切替処理
//	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//	{
//		if (++image_type > 5)
//		{
//			image_type = 0;
//		}
//	}
//
//	//x座標の更新
//	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定
//
//	if (is_facing_left) //フラグがTRUEの間、左に動き続ける。
//	{
//		location.x -= speed.x;
//	}
//	else
//	{
//		location.x += speed.x;
//	}
//
//	if (stage->HitBlock(this))
//	{
//		while (stage->HitBlock(this)) //進行方向とは逆に進み当たり判定から脱出
//		{
//			if (is_facing_left)
//			{
//				location.x += speed.x;
//			}
//			else
//			{
//				location.x -= speed.x;
//			}
//		}
//		roundtrips++;
//		is_facing_left = !is_facing_left;
//
//		if (roundtrips > num)
//		{
//			num = GetRand(3);
//			state = BLACKMAGE_STATE::ATTACK_STANDBY;
//			roundtrips = 0;
//			time = 0;
//			old_hp = hp;
//		}
//	}
//
//}
//
//void BlackMage::Standby()
//{
//
//	if (animation_time % 12 == 0)
//	{
//		if (++animation_type > 9)
//		{
//			animation_type = 0;
//		}
//	}
//
//	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
//	location.y += speed.y;
//
//	if (stage->HitBlock(this))
//	{
//		location.y -= speed.y;
//	}
//
//
//	if (++time % 600 == 0)
//	{
//		state = BLACKMAGE_STATE::ATTACK;
//		animation_type = 0;
//	}
//
//
//}
//
//void BlackMage::Wait()
//{
//
//	//location.y--;
//
//	if (++time % 200 == 0)
//	{
//		image_type = 6;
//		state = BLACKMAGE_STATE::TELEPORT;
//	}
//
//
//
//}
//
//void BlackMage::Attack()
//{
//	if (is_facing_left)
//	{
//		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,60 }, { -10,0 }, 10, 3, ATTACK_TYPE::FIRE_BALL, 3.0f);
//	}
//	else
//	{
//		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,60 }, { +10,0 }, 10, 3, ATTACK_TYPE::FIRE_BALL, 3.0f);
//	}
//
//	state = BLACKMAGE_STATE::WAIT;
//}
//
//void BlackMage::MoveAttack()
//{
//	if (++time % 60 == 0)
//	{
//		attack_manager->AddEnemyAttack({ location.x,location.y }, { 60,60 }, { 0,+10 }, 10, 5, ATTACK_TYPE::FIRE_BALL, 2.0f);
//	}
//}
//
//void BlackMage::TeleportAttack()
//{
//	location = { 8900,300 };
//
//	if (animation_time % 12 == 0)
//	{
//		++animation_type;
//		++image_type;
//
//
//		if (image_type > 9)
//		{
//			image_type = 6;
//		}
//
//
//		if (start_animation)
//		{
//			if (animation_type > 2)
//			{
//				animation_type = 2;
//			}
//		}
//		else
//		{
//
//			if (animation_type > 9)
//			{
//				animation_type = 0;
//			}
//		}
//
//	}
//
//	if (lock_on)
//	{
//		if (attack)
//		{
//			if (++time % 120 == 0)
//			{
//				attack_manager->AddEnemyAttack({ attack_location.x,300 }, { 30,250 }, { 0,0 }, 3, 10, ATTACK_TYPE::FIRE_BALL, 0);
//				attack = false;
//				start_animation = true;
//				time = 0;
//			}
//		}
//		else
//		{
//			if (++time % 300 == 0)
//			{
//				time = 0;
//				lock_on = false;
//				state = BLACKMAGE_STATE::NORMAL;
//				start_animation = false;
//				animation_type = 0;
//			}
//		}
//	}
//	else
//	{
//		if (++time % 600 == 0)
//		{
//			lock_on = true;
//			attack = true;
//			animation_type = 0;
//		}
//
//		attack_location = player_manager->GetPlayerData()->GetLocation();
//	}
//
//}
//
//float BlackMage::CalculateDistance()
//{
//	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
//	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
//	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）
//
//	float angle = atan2(dy, dx) * 180 / M_PI;
//
//	if (angle >= -45 && angle <= 85)
//	{
//		direction = true;
//	}
//	else
//	{
//		direction = false;
//	}
//
//	return distance;
//}
