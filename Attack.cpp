#include"DxLib.h"
#include"Attack.h"

Attack::Attack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image) : BoxCollider(location, size),
duration_time(duration_time),speed(speed),attack_power(attack_power), attack_image(attack_image)
{

}

Attack::~Attack()
{

}

bool Attack::Update(float delta_time)
{
	if ((duration_time -= delta_time) > 0.0f)
	{
		location.x += speed.x;
		location.y += speed.y;
		return false;
	}
	return true;
}

void Attack::Draw(float camera_work)const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))
	{
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xffffff, FALSE);
		//DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, player_image[0], TRUE);
	}
}

int Attack::GetAttackPower()const
{
	return attack_power;
}