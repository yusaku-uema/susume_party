//#include"DxLib.h"
//#include"Slime.h"
//#include"Stage.h"
//
//#define SLIME_SIZE_X 10.0f//サイズ
//#define SLIME_SIZE_Y 10.0f//サイズ
//
//#define WALK_SPEED 1.5f//1フレームの最大速
//#define ACCELERATION 0.1f//歩く時の加速
//#define ATTACK_DISTANCE 35// 攻撃に移る距離
//#define MAX_HP 20
//
//#define IMAGE_CHANGE_TIME 0.2f //画像切り替え時間
//
////-----------------------------------
////コンストラクタ
////-----------------------------------
//Slime::Slime(DATA location, int enemy_image[ENEMY_STATE::END][5], class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : 
//EnemyBase(location, { SLIME_SIZE_X , SLIME_SIZE_Y }, MAX_HP, 5, 5, enemy_image)
//{
//	this->stage = stage;
//	this->player_manager = player_manager;
//	this->attack_manager = attack_manager;
//
//	enemy_control_time = 0.0f;
//
//	OutputDebugString("Slimeコンストラクタ呼ばれました。\n");
//}
//
////-----------------------------------
////デストラクタ
////-----------------------------------
//Slime::~Slime()
//{
//	OutputDebugString("Slimeデストラクタが呼ばれました。\n");
//}
//
////-----------------------------------
////更新処理
////-----------------------------------
//void Slime::Update(float delta_time)
//{
//	//Y座標更新
//
//	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
//
//	location.y += speed.y;
//
//	if (stage->HitBlock(this))
//	{
//		location.y -= speed.y;
//		speed.y = 0.0f;
//	}
//
//	//状態ごとの処理
//
//	enemy_control_time += delta_time;
//
//	////////
//
//	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
//	{
//		draw_image_num++;
//		image_change_time = 0.0f;
//	}
//
//	if (ScopeoOfActivity())is_facing_left = !is_facing_left;
//
//	switch (enemy_state)
//	{
//	case ENEMY_STATE::NORMAL:
//		Move();
//		break;
//	case SLIME_STATE::ATTACK:
//		Attack();
//		break;
//	case SLIME_STATE::STANDBY:
//		Standby();
//		break;
//	case SLIME_STATE::DEATH:
//		//画像切替処理
//		if (animation_time % 12 == 0)
//		{
//			if (++image_type > 3)
//			{
//				is_dead = true;
//			}
//		}
//		break;
//	}
//	
//	if (location.y > 720)
//	{
//		is_dead = true;
//	}
//
//
//}
//
//
////-----------------------------------
////描画処理
////-----------------------------------
//void Slime::Draw() const
//{
//	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};
//
//	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))//画面内にブロックがある場合
//	{
//		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, slime_image[image_type], TRUE, !move_left);
//
//		DrawHPBar(MAX_HP);
//
//	}
//}
//
//
////-----------------------------------
////移動
////-----------------------------------
//void Slime::Move()
//{
//
//	//画像切替処理
//	if (animation_time % 12 == 0)
//	{
//		if (++image_type > 3)
//		{
//			image_type = 0;
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
//	//x座標の更新
//	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定
//
//	if (move_left) //左に進行するのか
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
//		move_left = !move_left;
//	}
//
//
//	if (CalculateDistance() < ATTACK_DISTANCE)
//	{
//		state = SLIME_STATE::ATTACK;
//	}
//
//}
//
//
////-----------------------------------
////攻撃
////-----------------------------------
//void Slime::Attack()
//{
//	//当たり判定の処理を書く
//	//画像切替処理
//	if (animation_time % 12 == 0)
//	{
//		if (++image_type > 8)
//		{
//			if (player_manager->CheckHitDamage(this, 10))
//			{
//				state = SLIME_STATE::STANDBY;
//			}
//			image_type = 4;
//		}
//	}
//
//	if (CalculateDistance() > ATTACK_DISTANCE || stage->HitBlock(this))
//	{
//		state = SLIME_STATE::NORMAL;
//	}
//
//	ENEMY_STATE::PREPARING_ATTACK
//}
//
//void Slime::Standby()
//{
//	if (animation_time % 12 == 0)
//	{
//		if (++image_type > 11)
//		{
//			image_type = 9;
//		}
//	}
//
//	if (++time % 120 == 0)
//	{
//		state = SLIME_STATE::NORMAL;
//	}
//}
//
//
////-----------------------------------
////相手との距離を測る
////-----------------------------------
//float Slime::CalculateDistance()
//{
//
//	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
//	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
//	 distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）
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
