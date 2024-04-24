#include"DxLib.h"
#include "Bird.h"

#define SLIME_SIZE 30.0f//サイズ
#define WALK_SPEED 1.5f//1フレームの最大速
#define ACCELERATION 0.1f//移動時の加速
#define UP_SPEED 0.1f //上昇、下降の速度
#define FALL_MAX 5  //上昇、下降の上限

Bird::Bird() : CharacterBase({ 900.0f, 50.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Birdコンストラクタ呼ばれました。\n");

	distance_moved = 0;

	start_attack = false;
	move_up = false;
	move_left = true;

}

Bird::~Bird()
{
	OutputDebugString("Birdデストラクタが呼ばれました。\n");
}

void Bird::Update(float delta_time, Stage* stage, class PlayerManager* player)
{

	if (start_attack)
	{
		
	}
	else
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

		//先頭プレイヤーとの距離が300以下なら攻撃開始
		if (CalculateDistance(player) < 300)
		{
			start_attack = true;
		}
	}

}

void Bird::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//画面内にブロックがある場合
	{
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
	}
}

float Bird::CalculateDistance(PlayerManager* player)
{
	float dx = player->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player->GetPlayerLocation().y - this->GetLocation().y;
	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

	return distance;
}
