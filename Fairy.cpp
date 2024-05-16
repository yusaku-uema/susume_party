#include "Fairy.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>


#define FAIRY_SIZE 64
#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���
#define UP_SPEED 0.1f //�㏸�A���~�̑��x
#define FALL_MAX 7.5  //�㏸�A���~�̏��
#define SEARCH_RANGE 300 //��틗��
#define IMAGE_SWITCHING_TIMING 12 //�摜�ؑփ^�C�~���O
#define WAITING_TIME_FOR_ATTACK 60 //�U���ҋ@���ԁi�U���^�C�~���O�j


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Fairy::Fairy() : CharacterBase({ 1400.0f, 50.0f }, { FAIRY_SIZE, FAIRY_SIZE }, 20, 10, 5, 5)
{

	OutputDebugString("�d���R���X�g���N�^�Ă΂�܂����B\n");

	if (LoadDivGraph("image/Enemy/fairy.png", 12, 12, 1, 64, 64, fairy_image) == -1)throw("�d���摜�Ǎ��ݎ��s\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	start_attack = false;
	standby_attack = false;
	move_left = true;
	direction = true;
	lock_on = false;


	state = FAIRY_STATE::NORMAL;

}


//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Fairy::~Fairy()
{
	OutputDebugString("�d���f�X�g���N�^���Ă΂�܂����B\n");
	for (int  i = 0; i < 12; i++)
	{
		DeleteGraph(fairy_image[i]);
	}
}


//-----------------------------------
//�X�V����
//-----------------------------------
void Fairy::Update(float delta_time, Stage* stage, PlayerManager* player)
{
	switch (state)
	{
	case FAIRY_STATE::NORMAL:
		Move(stage, player);
		break;
	case FAIRY_STATE::ATTACK:

		break;
	case FAIRY_STATE::STANDBY:

		break;
	default:
		break;
	}
}


//-----------------------------------
//�`��
//-----------------------------------
void Fairy::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{

		if (state == FAIRY_STATE::STANDBY || state == FAIRY_STATE::ATTACK)
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, fairy_image[image_type], TRUE, direction);
		}
		else
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, fairy_image[image_type], TRUE, !move_left);
		}

	}
}


//-----------------------------------
//�ړ�
//-----------------------------------
void Fairy::Move(Stage* stage, PlayerManager* player)
{
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

	////�擪�v���C���[�Ƃ̋�����SEARCH_RANGE�ȉ��Ȃ�U������
	//if (CalculateDistance(player) < SEARCH_RANGE)
	//{
	//	standby_attack = true;
	//	state = BIRD_STATE::STANDBY;
	//	image_type = 7;
	//}


}


//-----------------------------------
//�ҋ@
//-----------------------------------
void Fairy::Standby(PlayerManager* player)
{

}


//-----------------------------------
//�U��
//-----------------------------------
void Fairy::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

}


//-----------------------------------
//����Ƃ̋����𑪂�
//-----------------------------------
float Fairy::CalculateDistance(PlayerManager* player)
{
	return 0.0f;
}
