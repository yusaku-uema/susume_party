//#include"DxLib.h"
//#include"Bird.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//#define BIRD_SIZE 9.5f//サイズ
//#define WALK_SPEED 1.5f//1フレームの最大速
//#define ACCELERATION 0.1f//移動時の加速
//#define UP_SPEED 0.1f //上昇、下降の速度
//#define FALL_MAX 7.5  //上昇、下降の上限
//#define SEARCH_RANGE 300 //交戦距離
//#define IMAGE_SWITCHING_TIMING 12 //画像切替タイミング
//#define WAITING_TIME_FOR_ATTACK 60 //攻撃待機時間（攻撃タイミング）
//#define MAX_HP 10
//
////-----------------------------------
////コンストラクタ
////-----------------------------------
//Bird::Bird(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
//{
//	this->stage = stage;
//	this->player_manager = player_manager;
//	this->attack_manager = attack_manager;
//
//	OutputDebugString("Birdコンストラクタ呼ばれました。\n");
//
//	if (LoadDivGraph("image/Enemy/Bird.png", 11, 11, 1, 80, 80, bird_image) == -1)throw("バード画像読込み失敗\n");
//
//	image_type = 0;
//	animation_time = 0;
//
//	time = 0;
//
//	attack_speed = 0;
//	distance_moved = 0;
//
//	angle = 0;
//
//	move_up = false;
//	move_left = false;
//	direction = true;
//	lock_on = false;
//
//	state = BIRD_STATE::NORMAL;
//
//
//	this->location = location;
//	spawn_location = location;
//
//	////テスト 座標
//	//this->location = { 900.0f, 250.0f };
//	this->radius = { BIRD_SIZE ,BIRD_SIZE };
//	this->hp = MAX_HP;
//}
//
////-----------------------------------
////デストラクタ
////-----------------------------------
//Bird::~Bird()
//{
//	OutputDebugString("Birdデストラクタが呼ばれました。\n");
//	for (int i = 0; i < 11; i++)
//	{
//		DeleteGraph(bird_image[i]);
//	}
//}
//
//
////-----------------------------------
//// 更新処理
////-----------------------------------
//void Bird::Update()
//{
//	//アニメーション時間更新
//	++animation_time;
//
//	if (ScopeoOfActivity(stage->GetCameraWork()))
//	{
//		move_left=!move_left;
//	}
//	switch (state)
//	{
//	case BIRD_STATE::NORMAL: //通常移動
//		Move();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 3)
//			{
//				image_type = 0;
//			}
//		}
//
//		break;
//	case BIRD_STATE::STANDBY: //攻撃準備（待機）
//		Standby();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 10)
//			{
//				image_type = 7;
//			}
//		}
//
//		break;
//	case BIRD_STATE::ATTACK: //攻撃
//		Attack();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 6)
//			{
//				image_type = 4;
//			}
//		}
//
//		break;
//	case BIRD_STATE::RETURN:
//		Return();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 3)
//			{
//				image_type = 0;
//			}
//		}
//
//		break;
//	}
//}
//
////-----------------------------------
//// 描画
////-----------------------------------
//void Bird::Draw() const
//{
//	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };
//
//	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))//画面内にブロックがある場合
//	{
//		if (state == BIRD_STATE::ATTACK || state == BIRD_STATE::STANDBY)
//		{
//			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, direction);
//		}
//		else
//		{
//			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, !move_left);
//		}
//		//DrawFormatString(draw_location.x, draw_location.y - 100, 0xffffff, "	角度 =%f", angle);
//		////DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x00ffff, FALSE);
//
//		DrawHPBar(MAX_HP);
//	}
//}
//
//
////-----------------------------------
//// 通常移動(右に動くか左に動くか)
////-----------------------------------
//void Bird::Move()
//{
//
//	//x座標の更新
//	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//スピードに加速度を足していって、最大値に達したら固定
//
//	if (move_left)
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
//
//			if (move_left)
//			{
//				location.x += speed.x;
//			}
//			else
//			{
//				location.x -= speed.x;
//			}
//		}
//
//		move_left = !move_left;
//	}
//
//	//先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃準備
//	if (CalculateDistance() < SEARCH_RANGE)
//	{
//		state = BIRD_STATE::STANDBY;
//		image_type = 7;
//	}
//
//
//}
//
////-----------------------------------
//// 攻撃準備(待機)
////-----------------------------------
//void Bird::Standby()
//{
//
//	//先頭プレイヤーとの距離がSEARCH_RANGE以下なら攻撃開始
//	if (CalculateDistance() < SEARCH_RANGE)
//	{
//		if (++time % WAITING_TIME_FOR_ATTACK == 0)
//		{
//			state = BIRD_STATE::ATTACK;
//			player_location = player_manager->GetPlayerData()->GetLocation();
//			old_location = location;
//			time = 0;
//		}
//	}
//	else //距離が離れたら通常移動へ
//	{
//		state = BIRD_STATE::NORMAL;
//		time = 0;
//	}
//
//}
//
////-----------------------------------
//// 攻撃時の移動
////-----------------------------------
//void Bird::Attack()
//{
//	CalculateDistance();
//
//	dx = player_location.x - location.x;
//	dy = player_location.y - location.y;
//	distance = sqrtf(dx * dx + dy * dy);
//
//	angle = atan2(dy, dx) * 180 / M_PI;
//
//	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定
//
//	if (stage->HitBlock(this))
//	{
//		state = BIRD_STATE::RETURN;
//		attack_speed = 0;
//		lock_on = false;
//	}
//	else
//	{
//		if (distance > 5)
//		{
//			location.x += (dx / distance) * attack_speed;
//			location.y += (dy / distance) * attack_speed;
//		}
//		else
//		{
//			state = BIRD_STATE::RETURN;
//			attack_speed = 0;
//		}
//	}
//
//	if (player_manager->CheckHitDamage(this, 5))
//	{
//		state = BIRD_STATE::RETURN;
//		attack_speed = 0;
//	}
//}
//
//
////-----------------------------------
//// 待機していた位置に戻る
////-----------------------------------
//void Bird::Return()
//{
//	float dx = old_location.x - location.x;
//	float dy = old_location.y - location.y;
//	float distance = sqrtf(dx * dx + dy * dy);
//
//
//	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定
//
//	if (distance >= 5)
//	{
//		location.x += (dx / distance) * FALL_MAX;
//		location.y += (dy / distance) * FALL_MAX;
//	}
//	else
//	{
//		attack_speed = 0;
//		state = BIRD_STATE::NORMAL;
//	}
//}
//
////-----------------------------------
//// 先頭にいるプレイヤーとの当たり判定
////-----------------------------------
//float Bird::CalculateDistance() {
//	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
//	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
//	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）
//
//	float angle = atan2(dy, dx) * 180 / M_PI;
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
//
//
//}
