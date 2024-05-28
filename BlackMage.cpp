#include "BlackMage.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BLACKMAGE_SIZE 132
#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���
#define UP_SPEED 0.1f //�㏸�A���~�̑��x
#define FALL_MAX 7.5  //�㏸�A���~�̏��
#define SEARCH_RANGE 300 //��틗��
#define IMAGE_SWITCHING_TIMING 12 //�摜�ؑփ^�C�~���O
#define WAITING_TIME_FOR_ATTACK 60 //�U���ҋ@���ԁi�U���^�C�~���O�j


BlackMage::BlackMage(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : EnemyBase()
{
	OutputDebugString("�����m�R���X�g���N�^�Ă΂�܂����B\n");


	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/blackmage.png", 14, 14, 1, 131, 132, blackmage_image) == -1)throw("�����m�i�{�X�j���Ǎ��ݎ��s\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	move_left = true;
	direction = true;
	lock_on = false;


	state = BLACKMAGE_STATE::WAIT;

	//�e�X�g ���W
	this->location = { 1000,400 };


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

		break;
	case BLACKMAGE_STATE::ATTACK_STANDBY:

		break;
	case BLACKMAGE_STATE::STANDBY:

		break;
	default:
		break;
	}
}

void BlackMage::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{


		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, blackmage_image[image_type], TRUE, !move_left);


	}
}

void BlackMage::Move()
{
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

	if (move_left) //�t���O��TRUE�̊ԁA���ɓ���������B
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

}

void BlackMage::Standby()
{

}

void BlackMage::Wait()
{
	//�擪�v���C���[�Ƃ̋�����SEARCH_RANGE�ȉ��Ȃ�U������
	if (CalculateDistance() < SEARCH_RANGE)
	{
		state = BLACKMAGE_STATE::NORMAL;
	}
}

void BlackMage::Attack()
{

}

float BlackMage::CalculateDistance()
{
	return 0.0f;
}
