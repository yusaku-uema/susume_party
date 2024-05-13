#include"DxLib.h"
#include"Bird.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 7.5  //上昇、下降の上限

//-----------------------------------
//コンストラクタ
//-----------------------------------
Bird::Bird() : CharacterBase({ 900.0f, 100.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Birdコンストラクタ呼ばれました。\n");

	if (LoadDivGraph("image/Enemy/Bird.png", 11, 11, 1, 80, 80, bird_image) == -1)throw("バード画像読込み失敗\n");
	

	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
    distance_moved = 0;


	start_attack = false;
	standby_attack = false;
	move_up = false;
	move_left = true;
	direction = true;
	lock_on = false;


	state = BIRD_STATE::NORMAL;

}

//-----------------------------------
//デストラクタ
//-----------------------------------
Bird::~Bird()
{
	OutputDebugString("Birdデストラクタが呼ばれました。\n");
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(bird_image[i]);
	}
}


//-----------------------------------
// 更新処理
//-----------------------------------
void Bird::Update(float delta_time, Stage* stage, class PlayerManager* player)
{
	//アニメーション時間更新
	++animation_time;

	switch (state)
	{
	case BIRD_STATE::NORMAL: //通常移動
		Move(stage, player);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 3)
			{
				image_type = 0;
			}
		}

		break;
	case BIRD_STATE::STANDBY: //攻撃準備（待機）
		Standby(player);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 10)
			{
				image_type = 7;
			}
		}

		break;
	case BIRD_STATE::ATTACK: //攻撃
		Attack(stage, player, delta_time);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 6)
			{
				image_type = 4;
			}
		}

		break;
	case BIRD_STATE::RETURN:
		Retur();

		if (animation_time % 12 == 0)
		{
			if (++image_type > 3)
			{
				image_type = 0;
			}
		}

		break;
	}



	

}

//-----------------------------------
// 描画
//-----------------------------------
void Bird::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
		
		
		if (state == BIRD_STATE::STANDBY || state == BIRD_STATE::ATTACK)
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, direction);
		}
		else
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, !move_left);
		}

	}
}


//-----------------------------------
// 通常移動(右に動くか左に動くか)
//-----------------------------------
void Bird::Move(Stage* stage, PlayerManager* player)
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

	//先頭プレイヤーとの距離が300以下なら攻撃準備
	if (CalculateDistance(player) < 300)
	{
		standby_attack = true;
		state = BIRD_STATE::STANDBY;
		image_type = 7;
	}


}

//-----------------------------------
// 攻撃準備(待機)
//-----------------------------------
void Bird::Standby(PlayerManager* player)
{

	//先頭プレイヤーとの距離が300以下なら攻撃開始
	if (CalculateDistance(player) < 300)
	{
		if (++time % 120 == 0)
		{
			state = BIRD_STATE::ATTACK;
			old_location = location;
			time = 0;
		}
	}
	else //距離が離れたら通常移動へ
	{
		standby_attack = false;
		state = BIRD_STATE::NORMAL;
		time = 0;
	}

}

//-----------------------------------
// 攻撃時の移動
//-----------------------------------
void Bird::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

	if (lock_on)
	{
		 dx = player_location.x - location.x;
		 dy = player_location.y - location.y;
		distance = sqrtf(dx * dx + dy * dy);
	}
	else
	{
		float dx = player->GetPlayerLocation().x - location.x;
		float dy = player->GetPlayerLocation().y - location.y;
		distance = sqrtf(dx * dx + dy * dy);
	}

	
	
	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定



	if (stage->HitBlock(this))
	{
		state = BIRD_STATE::RETURN;
		attack_speed = 0;
		lock_on = false;
	}
	else
	{

		if (distance > 20 && lock_on == false)
		{
			lock_on = true;
			player_location = player->GetPlayerLocation(); //座標更新
		}
		else if (distance > 5)  //ここに、プレイヤーに当たったか、壁に当たったのかを書くこと
		{
			location.x += (dx / distance) * FALL_MAX;
			location.y += (dy / distance) * FALL_MAX;
		}
		else
		{
			attack_speed = 0;
			state = BIRD_STATE::RETURN;
			lock_on = false;
		}
	}

}


//-----------------------------------
// 待機していた位置に戻る
//-----------------------------------
void Bird::Retur()
{
	float dx = old_location.x - location.x;
	float dy = old_location.y - location.y;
	float distance = sqrtf(dx * dx + dy * dy);


	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定

	if (distance >= 5)
	{
		location.x += (dx / distance) * FALL_MAX;
		location.y += (dy / distance) * FALL_MAX;
	}
	else
	{
		attack_speed = 0;
		state = BIRD_STATE::NORMAL;
	}
}

//-----------------------------------
// 先頭にいるプレイヤーとの当たり判定
//-----------------------------------
float Bird::CalculateDistance(PlayerManager* player)
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
