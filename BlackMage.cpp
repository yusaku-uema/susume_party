#include "BlackMage.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BLACKMAGE_SIZE 20
#define WALK_SPEED 2.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���
#define UP_SPEED 0.1f //�㏸�A���~�̑��x
#define FALL_MAX 7.5  //�㏸�A���~�̏��
#define SEARCH_RANGE 300 //���G�͈�
#define IMAGE_SWITCHING_TIMING 12 //�摜�ؑփ^�C�~���O
#define WAITING_TIME_FOR_ATTACK 60 //�U���ҋ@���ԁi�U���^�C�~���O�j


BlackMage::BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
{
	OutputDebugString("�����m�R���X�g���N�^�Ă΂�܂����B\n");


	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/blackmage.png", 14, 14, 1, 131, 132, blackmage_image) == -1)throw("�����m�i�{�X�j���Ǎ��ݎ��s\n");

	this->hp = 150;
	image_type = 0;
	animation_time = 0;
	roundtrips = 0;
	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	is_facing_left = true;
	direction = true;
	lock_on = false;


	state = BLACKMAGE_STATE::WAIT;

	////�e�X�g ���W
	//this->location = { 2300,330 };
	this->location = location;
	this->radius = { BLACKMAGE_SIZE, BLACKMAGE_SIZE };


}

BlackMage::~BlackMage()
{
	OutputDebugString("�{�X�i�������m�j�f�X�g���N�^���Ă΂�܂����B\n");
	for (int i = 0; i < 14; i++)
	{
		DeleteGraph(blackmage_image[i]);
	}
}

void BlackMage::Update()
{

	//�A�j���[�V�������ԍX�V
	++animation_time;


	switch (state)
	{
	case BLACKMAGE_STATE::WAIT:
		Wait(); //�v���C���[��������܂ŉ������Ȃ��j�[�g
		break;
	case BLACKMAGE_STATE::NORMAL:
		Move(); //����
		break;
	case BLACKMAGE_STATE::ATTACK:
		Attack();
		break;
	case BLACKMAGE_STATE::ATTACK_STANDBY:
		Standby();
		break;
	case BLACKMAGE_STATE::STANDBY:

		break;
	default:
		break;
	}

	if (hp <= 0)
	{
		is_dead = true;
	}

}

void BlackMage::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{
		DrawRotaGraph(draw_location.x, draw_location.y - 20, 1, 0, blackmage_image[image_type], TRUE, !is_facing_left);
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x00ffff, FALSE);
	}
}

void BlackMage::Move()
{

	MoveAttack();

	//�摜�ؑ֏���
	if (animation_time % IMAGE_SWITCHING_TIMING == 0)
	{
		if (++image_type > 5)
		{
			image_type = 0;
		}
	}

	//x���W�̍X�V
	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�

	if (is_facing_left) //�t���O��TRUE�̊ԁA���ɓ���������B
	{
		location.x -= speed.x;
	}
	else
	{
		location.x += speed.x;
	}

	if (stage->HitBlock(this))
	{
		while (stage->HitBlock(this)) //�i�s�����Ƃ͋t�ɐi�ݓ����蔻�肩��E�o
		{
			if (is_facing_left)
			{
				location.x += speed.x;
			}
			else
			{
				location.x -= speed.x;
			}
		}
		roundtrips++;
		is_facing_left = !is_facing_left;

		if (roundtrips > 2)
		{
			state = BLACKMAGE_STATE::ATTACK_STANDBY;
			roundtrips = 0;
			time = 0;
			old_hp = hp;
		}
	}

}

void BlackMage::Standby()
{

	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		location.y -= speed.y;
	}

	if (old_hp - 20 < hp)
	{
		
	}

	if (++time % 600 == 0)
	{
		state = BLACKMAGE_STATE::ATTACK;
	}

	if (time % 60 == 0)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y}, { 40,40 }, { 0,0 }, -1, 20, ATTACK_TYPE::EXPLOSION, 1.0f);
	}

}

void BlackMage::Wait()
{
	if (lock_on)
	{

		location.y--;

		if (++time % 200 == 0)
		{
			state = BLACKMAGE_STATE::NORMAL;
		}
	}
	else
	{
		//�擪�v���C���[�Ƃ̋�����SEARCH_RANGE�ȉ��Ȃ瓮���o��
		if (CalculateDistance() < SEARCH_RANGE)
		{
			state = BLACKMAGE_STATE::NORMAL;
			lock_on = true;
		}
	}
	
}

void BlackMage::Attack()
{
	if (is_facing_left)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { -10,0 }, 10, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
	}
	else
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { +10,0 }, 10, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
	}

	state = BLACKMAGE_STATE::WAIT;
}

void BlackMage::MoveAttack()
{
	if (++time % 60 == 0)
	{
		attack_manager->AddEnemyAttack({ location.x,location.y }, { 40,40 }, { 0,+10 }, 10, 3, ATTACK_TYPE::EXPLOSION, 1.0f);
	}
}

float BlackMage::CalculateDistance()
{
	float dx = player_manager->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player_manager->GetPlayerLocation().y - this->GetLocation().y;
	float distance = sqrt(dx * dx + dy * dy); // ���[�N���b�h�����̌v�Z�i�����������j

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
