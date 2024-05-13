#include"DxLib.h"
#include"Bird.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SLIME_SIZE 30.0f//�T�C�Y
#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���
#define UP_SPEED 0.1f //�㏸�A���~�̑��x
#define FALL_MAX 7.5  //�㏸�A���~�̏��

//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Bird::Bird() : CharacterBase({ 900.0f, 100.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Bird�R���X�g���N�^�Ă΂�܂����B\n");

	if (LoadDivGraph("image/Enemy/Bird.png", 11, 11, 1, 80, 80, bird_image) == -1)throw("�o�[�h�摜�Ǎ��ݎ��s\n");
	

	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
    distance_moved = 0;


	start_attack = false;
	standby_attack = false;
	move_up = false;
	move_left = true;
	direction = true;
	lock_on = false;


	state = BIRD_STATE::NORMAL;

}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Bird::~Bird()
{
	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(bird_image[i]);
	}
}


//-----------------------------------
// �X�V����
//-----------------------------------
void Bird::Update(float delta_time, Stage* stage, class PlayerManager* player)
{
	//�A�j���[�V�������ԍX�V
	++animation_time;

	switch (state)
	{
	case BIRD_STATE::NORMAL: //�ʏ�ړ�
		Move(stage, player);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 3)
			{
				image_type = 0;
			}
		}

		break;
	case BIRD_STATE::STANDBY: //�U�������i�ҋ@�j
		Standby(player);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 10)
			{
				image_type = 7;
			}
		}

		break;
	case BIRD_STATE::ATTACK: //�U��
		Attack(stage, player, delta_time);

		if (animation_time % 12 == 0)
		{
			if (++image_type > 6)
			{
				image_type = 4;
			}
		}

		break;
	case BIRD_STATE::RETURN:
		Retur();

		if (animation_time % 12 == 0)
		{
			if (++image_type > 3)
			{
				image_type = 0;
			}
		}

		break;
	}



	

}

//-----------------------------------
// �`��
//-----------------------------------
void Bird::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{
		//DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
		
		
		if (state == BIRD_STATE::STANDBY || state == BIRD_STATE::ATTACK)
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, direction);
		}
		else
		{
			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, !move_left);
		}

	}
}


//-----------------------------------
// �ʏ�ړ�(�E�ɓ��������ɓ�����)
//-----------------------------------
void Bird::Move(Stage* stage, PlayerManager* player)
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

	//�擪�v���C���[�Ƃ̋�����300�ȉ��Ȃ�U������
	if (CalculateDistance(player) < 300)
	{
		standby_attack = true;
		state = BIRD_STATE::STANDBY;
		image_type = 7;
	}


}

//-----------------------------------
// �U������(�ҋ@)
//-----------------------------------
void Bird::Standby(PlayerManager* player)
{

	//�擪�v���C���[�Ƃ̋�����300�ȉ��Ȃ�U���J�n
	if (CalculateDistance(player) < 300)
	{
		if (++time % 120 == 0)
		{
			state = BIRD_STATE::ATTACK;
			old_location = location;
			time = 0;
		}
	}
	else //���������ꂽ��ʏ�ړ���
	{
		standby_attack = false;
		state = BIRD_STATE::NORMAL;
		time = 0;
	}

}

//-----------------------------------
// �U�����̈ړ�
//-----------------------------------
void Bird::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

	if (lock_on)
	{
		 dx = player_location.x - location.x;
		 dy = player_location.y - location.y;
		distance = sqrtf(dx * dx + dy * dy);
	}
	else
	{
		float dx = player->GetPlayerLocation().x - location.x;
		float dy = player->GetPlayerLocation().y - location.y;
		distance = sqrtf(dx * dx + dy * dy);
	}

	
	
	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�



	if (stage->HitBlock(this))
	{
		state = BIRD_STATE::RETURN;
		attack_speed = 0;
		lock_on = false;
	}
	else
	{

		if (distance > 20 && lock_on == false)
		{
			lock_on = true;
			player_location = player->GetPlayerLocation(); //���W�X�V
		}
		else if (distance > 5)  //�����ɁA�v���C���[�ɓ����������A�ǂɓ��������̂�����������
		{
			location.x += (dx / distance) * FALL_MAX;
			location.y += (dy / distance) * FALL_MAX;
		}
		else
		{
			attack_speed = 0;
			state = BIRD_STATE::RETURN;
			lock_on = false;
		}
	}

}


//-----------------------------------
// �ҋ@���Ă����ʒu�ɖ߂�
//-----------------------------------
void Bird::Retur()
{
	float dx = old_location.x - location.x;
	float dy = old_location.y - location.y;
	float distance = sqrtf(dx * dx + dy * dy);


	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�

	if (distance >= 5)
	{
		location.x += (dx / distance) * FALL_MAX;
		location.y += (dy / distance) * FALL_MAX;
	}
	else
	{
		attack_speed = 0;
		state = BIRD_STATE::NORMAL;
	}
}

//-----------------------------------
// �擪�ɂ���v���C���[�Ƃ̓����蔻��
//-----------------------------------
float Bird::CalculateDistance(PlayerManager* player)
{
	float dx = player->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player->GetPlayerLocation().y - this->GetLocation().y;
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
