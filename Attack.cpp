#include"DxLib.h"
#include"Attack.h"

Attack::Attack(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager,
	DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image) : 
	BoxCollider(location, size),stage(stage), player_manager(player_manager), enemy_manager(enemy_manager),
duration_time(duration_time),speed(speed),attack_power(attack_power), attack_image(attack_image)
{

	if (LoadDivGraph("image/Player/explosion.png", 8,8, 1, 48, 48, explosion_image) == -1)throw("image/Player/explosion.pngが読み込めません\n");

	image = explosion_image;
	image_num = 8;
	draw_image_num = 0;
	change_image_time = 0.0f;
	

	OutputDebugString("Attackコンストラクタ呼ばれました。\n");
}

Attack::~Attack()
{
	OutputDebugString("Attackコンストラクタ呼ばれました。\n");
}

bool Attack::Update(float delta_time, bool is_player_attack)
{
	location.x += speed.x;
	location.y += speed.y;

	if ((change_image_time += delta_time) > 0.08)
	{
		if (++draw_image_num > image_num - 1)return true;
		change_image_time = 0.0f;
	}

	if (stage->HitBlock(this))return true;

	return ((duration_time -= delta_time) < 0.0f);
}

void Attack::Draw()const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))
	{
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
		DrawRotaGraph(draw_location.x, draw_location.y, 5, 0, explosion_image[draw_image_num], TRUE);
	}
}

int Attack::GetAttackPower()const
{
	return attack_power;
}