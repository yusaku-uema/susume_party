#include"DxLib.h"
#include"Attack.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ATTACK_SPEED 3
#define IMAGE_CHANGE_TIME 0.1f

Attack::Attack(DATA location, DATA size, DATA speed, BoxCollider* target, float duration_time, int attack_power, int* attack_image, int image_num, float image_size) :
	BoxCollider(location, size), speed(speed), target(target), duration_time(duration_time), attack_power(attack_power), attack_image(attack_image),
	image_num(image_num), image_size(image_size), draw_image_num(0), image_change_time(0.0f)
{
	OutputDebugString("Attack�R���X�g���N�^�Ă΂�܂����B\n");
}

Attack::~Attack()
{
	OutputDebugString("Attack�f�X�g���N�^�Ă΂�܂����B\n");
}

bool Attack::Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, EnemyManager* enemy_manager)
{
	if (player_manager != nullptr)
	{
		target = player_manager->GetPlayerData();
	}

	//�ǔ�����ꍇ

	if (target != nullptr)TrackingCharacter();

	location.x += speed.x;
	location.y += speed.y;
	

	//�摜�؂�ւ�

	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
	{
		if (++draw_image_num > image_num - 1)
		{
			if (duration_time == -1.0f)return true;
			else draw_image_num = 0;
		}
		image_change_time = 0.0f;
	}

	//�U����������

	if (duration_time != -1.0f)
	{
		if ((duration_time -= delta_time) < 0.0f)return true;
	}

	//�����蔻��

	if ((radius.x != 0.0f) && (radius.y != 0.0f))
	{

		if (stage->HitBlock(this))
		{
			return true;
		}
		else
		{
			//�v���C���[�Ɠ���������
			if (player_manager != nullptr)
			{
				if (player_manager->CheckHitDamage(this, attack_power))return true;
			}
			//�G�L�����Ɠ��������ꍇ
			else if (enemy_manager != nullptr)
			{
				if (enemy_manager->CheckHitDamage(this, attack_power))return true;
			}
		}
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

void Attack::TrackingCharacter()
{
	//�ǐՎ҂̍��W�擾

	float dx = target->GetLocation().x - location.x;
	float dy = target->GetLocation().y - location.y;
	float distance = sqrt(dx * dx + dy * dy); // ���[�N���b�h�����̌v�Z�i�����������j

	angle = atan2(dy, dx) * 180 / M_PI;

	speed.x = (dx / distance) * 3;
	speed.y = (dy / distance) * 3;
}

void Attack::DeleteTargetPointer(BoxCollider* target)
{
	if (this->target == target)this->target = nullptr;
}