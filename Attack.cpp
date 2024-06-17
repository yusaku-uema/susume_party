#include"DxLib.h"
#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ATTACK_SPEED 3
#define IMAGE_CHANGE_TIME 0.1f

Attack::Attack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int* attack_image, int image_num, float image_size) :
	BoxCollider(location, size), duration_time(duration_time), speed(speed), attack_power(attack_power), attack_image(attack_image),
	image_num(image_num), image_size(image_size), draw_image_num(0), image_change_time(0.0f)
{
	OutputDebugString("Attackコンストラクタ呼ばれました。\n");
}

Attack::~Attack()
{
	OutputDebugString("Attackコンストラクタ呼ばれました。\n");
}

bool Attack::Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, EnemyManager* enemy_manager)
{
	location.x += speed.x;
	location.y += speed.y;

	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
	{
		if (++draw_image_num > image_num - 1)
		{
			if (duration_time == -1.0f)return true;
			else draw_image_num = 0;
		}
		image_change_time = 0.0f;
	}

	if ((radius.x != 0.0f) && (radius.y != 0.0f))
	{
		if (stage->HitBlock(this))return true;
		else
		{
			//キャラと当たった時
			if (player_manager != nullptr)
			{
				if (player_manager->CheckHitDamage(this, attack_power))return true;
			}
			else if (enemy_manager != nullptr)
			{
				if (enemy_manager->CheckHitDamage(this, attack_power))return true;
			}
		}
	}

	if (duration_time != -1.0f)
	{
		if ((duration_time -= delta_time) < 0.0f)return true;
	}

	return false;
}

void Attack::Draw(float camera_work)const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))
	{
		DrawRotaGraph(draw_location.x, draw_location.y, image_size, 0, *(attack_image + draw_image_num), TRUE);
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
	}
}

DATA Attack::TrackingCharacter(BoxCollider* target_location)
{
	//追跡者の座標取得
	float x = location.x; 
	float y = location.y;

	float dx = target_location->GetLocation().x - location.x;
	float dy = target_location->GetLocation().y - location.y;
	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

	float angle = atan2(dy, dx) * 180 / M_PI;

	x += (dx / distance) * ATTACK_SPEED;
	y += (dy / distance) * ATTACK_SPEED;
	
	DATA location = { x,y };

	return location;

}

int Attack::GetAttackPower()const
{
	return attack_power;
}