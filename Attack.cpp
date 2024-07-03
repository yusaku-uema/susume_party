#include"DxLib.h"
#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ATTACK_SPEED 7
#define IMAGE_CHANGE_TIME 0.1f

Attack::Attack(DATA location, DATA size, DATA speed, BoxCollider* target, bool delete_hit_stage, bool delete_hit_chara, 
	float duration_time, int attack_power, int* attack_image, int image_num, float image_size) :
	BoxCollider(location, size), speed(speed), target(target), delete_hit_stage(delete_hit_stage), delete_hit_chara(delete_hit_chara), 
	duration_time(duration_time), attack_power(attack_power), attack_image(attack_image),image_num(image_num), 
	image_size(image_size), draw_image_num(0), image_change_time(0.0f), angle(0)
{
	OutputDebugString("Attackコンストラクタ呼ばれました。\n");
}

Attack::~Attack()
{
	OutputDebugString("Attackデストラクタ呼ばれました。\n");
}

bool Attack::Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
	//追尾する場合
	if (target != nullptr)TargetTracking();

	location.x += speed.x;
	location.y += speed.y;
	
	//画像切り替え

	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
	{
		if (++draw_image_num > image_num - 1)
		{
			if (duration_time == -1.0f)return true;
			else draw_image_num = 0;
		}
		image_change_time = 0.0f;
	}

	//攻撃持続時間

	if (duration_time != -1.0f)
	{
		if ((duration_time -= delta_time) < 0.0f)return true;
	}

	//当たり判定

	if ((radius.x != 0.0f) && (radius.y != 0.0f))
	{
		if ((stage->HitBlock(this)) && (delete_hit_stage))return true;//ステージに当たった時
		else
		{
			if (player_manager != nullptr)//プレイヤーと当たった時
			{
				if ((player_manager->CheckHitDamage(this, attack_power)) && (delete_hit_chara))return true;
			}
			else if (enemy_manager != nullptr)//敵キャラと当たった場合
			{
				if ((enemy_manager->CheckHitDamage(this, attack_power)) && (delete_hit_chara))return true;
			}
		}
	}
	return false;
}

void Attack::Draw(float camera_work)const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))
	{
		DrawRotaGraph(draw_location.x, draw_location.y, image_size, 0, *(attack_image + draw_image_num), TRUE);
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
	}
}

void Attack::TargetTracking()
{
	//追跡者の座標取得
	float dx = target->GetLocation().x - location.x;
	float dy = target->GetLocation().y - location.y;
	float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

	//angle = atan2(dy, dx) * 180 / M_PI;

	speed.x = (dx / distance) * ATTACK_SPEED;
	speed.y = (dy / distance) * ATTACK_SPEED;
}

void Attack::DeleteTargetPointer(BoxCollider* target)
{
	if (this->target == target)this->target = nullptr;
}