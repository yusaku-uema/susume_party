#include"DxLib.h"
#include"Bird.h"
#include <math.h>

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 5  //上昇、下降の上限

//-----------------------------------
//コンストラクタ
//-----------------------------------
Bird::Bird() : CharacterBase({ 900.0f, 100.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Birdコンストラクタ呼ばれました。\n");

	
	time = 0;

	attack_speed = 0;
    distance_moved = 0;


	start_attack = false;
	standby_attack = false;
	move_up = false;
	move_left = true;


	state = BIRD_STATE::NORMAL;

}

//-----------------------------------
//デストラクタ
//-----------------------------------
Bird::~Bird()
{
	OutputDebugString("Birdデストラクタが呼ばれました。\n");
}


//-----------------------------------
// 更新処理
//-----------------------------------
void Bird::Update(float delta_time, Stage* stage, class PlayerManager* player)
{


	switch (state)
	{
	case BIRD_STATE::NORMAL: //通常移動
		Move(stage, player);
		break;
	case BIRD_STATE::STANDBY: //攻撃準備（待機）
		Standby(player);
		break;
	case BIRD_STATE::ATTACK: //攻撃
		Attack(stage, player, delta_time);
		break;
	case BIRD_STATE::RETURN:
		Retur();
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
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
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
	float dx = player->GetPlayerLocation().x - location.x;
	float dy = player->GetPlayerLocation().y - location.y;
	distance = sqrtf(dx * dx + dy * dy);
	
	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//スピードに加速度を足していって、最大値に達したら固定


	if (stage->HitBlock(this))
	{
		state = BIRD_STATE::RETURN;
		attack_speed = 0;
	}
	else
	{

		if (distance > 30)  //ここに、プレイヤーに当たったか、壁に当たったのかを書くこと
		{
			location.x += (dx / distance) * FALL_MAX;
			location.y += (dy / distance) * FALL_MAX;
		}
		else
		{
			attack_speed = 0;
			state = BIRD_STATE::RETURN;
		}
	}

}

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

	return distance;
}
