#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include"Slime.h"

#define SLIME_SIZE 20.0f//�T�C�Y
#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�������̉���
#define ATTACK_DISTANCE 38// �U���Ɉڂ鋗��


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Slime::Slime(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : EnemyBase()
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Enemy/Slime.png", 12, 12, 1, 48, 48, slime_image) == -1)throw("�X���C���摜�Ǎ��ݎ��s\n");
	image_type = 0;
	move_left = true;
	direction = true;

	time = 0;

	state = SLIME_STATE::NORMAL;

	//�e�X�g ���W
	this->location = { 600.0f, 300.0f };
	this->radius = { SLIME_SIZE ,SLIME_SIZE };

	OutputDebugString("Slime�R���X�g���N�^�Ă΂�܂����B\n");
}


//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Slime::~Slime()
{
	OutputDebugString("Slime�f�X�g���N�^���Ă΂�܂����B\n");
	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(slime_image[i]);
	}
}


//-----------------------------------
//�X�V����
//-----------------------------------
void Slime::Update()
{
	++time; //�A�j���[�V�������ԍX�V

	switch (state)
	{
	case SLIME_STATE::NORMAL:
		Move();

		//�摜�ؑ֏���
		if (time % 12 == 0)
		{
			if (++image_type > 3)
			{
				image_type = 0;
			}
		}

		break;
	case SLIME_STATE::ATTACK:
		Attack();

		//�摜�ؑ֏���
		if (time % 12 == 0)
		{
			if (++image_type > 8)
			{
				image_type = 4;
			}
		}

		break;
	}


}


//-----------------------------------
//�`�揈��
//-----------------------------------
void Slime::Draw() const
{
	DATA draw_location = { location.x + stage->GetCameraWork(), location.y};

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
		DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, slime_image[image_type], TRUE, !move_left);
	}
}


//-----------------------------------
//�ړ�
//-----------------------------------
void Slime::Move()
{
	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		location.y -= speed.y;
	}

	//x���W�̍X�V
	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�

	if (move_left) //���ɐi�s����̂�
	{
		location.x -= speed.x;
	}
	else
	{
		location.x += speed.x;
	}

	if (stage->HitBlock(this))
	{
		move_left = !move_left;
	}


	if (CalculateDistance() < ATTACK_DISTANCE)
	{
		state = SLIME_STATE::ATTACK;
	}

}


//-----------------------------------
//�U��
//-----------------------------------
void Slime::Attack()
{
	//�����蔻��̏���������

	if (move_left)
	{
		//�U��
		attack_manager->AddEnemyAttack({ location.x - 10,location.y }, { 40,40 }, { 0,0 }, 0.5, 3, ATTACK_TYPE::EXPLOSION);
	}
	else
	{
		//�U��
		attack_manager->AddEnemyAttack({ location.x + 10,location.y }, { 40,40}, { 0,0 }, 0.5, 3, ATTACK_TYPE::EXPLOSION);
	}


	if (CalculateDistance() > ATTACK_DISTANCE || stage->HitBlock(this))
	{
		state = SLIME_STATE::NORMAL;
	}

}


//-----------------------------------
//����Ƃ̋����𑪂�
//-----------------------------------
float Slime::CalculateDistance()
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
