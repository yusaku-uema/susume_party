#include"DxLib.h"
#include "Bird.h"

#define SLIME_SIZE 30.0f//�T�C�Y
#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���
#define UP_SPEED 0.1f //�㏸�A���~�̑��x
#define FALL_MAX 5  //�㏸�A���~�̏��

Bird::Bird() : CharacterBase({ 900.0f, 50.0f }, { SLIME_SIZE, SLIME_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("Bird�R���X�g���N�^�Ă΂�܂����B\n");

	distance_moved = 0;

	move_up = false;
	move_left = true;
	fly = true;

}

Bird::~Bird()
{
	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
}

void Bird::Update(float delta_time, Stage* stage)
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
		fly = false;//�ǂɓ��������ꍇ�A��ׂȂ��Ȃ��ė�����

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


	//y���W�̍X�V
		if (fly)
		{
			if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�
			if ((distance_moved += UP_SPEED) > FALL_MAX)distance_moved = 0, move_up = !move_up, speed.y = 0; //������

			if (move_up) //�t���O��TRUE�̏ꍇ�A�㏸����
			{
				location.y -= speed.y;
			}
			else
			{
				location.y += speed.y;
			}
			if (stage->HitBlock(this))fly = false;
		}
		else
		{
			if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;
			location.y += speed.y;
			if (stage->HitBlock(this))location.y -= speed.y;//�n�ʂɓ������Ă���ꍇ�A��L�̌v�Z�𑊎E����B
		}

}

void Bird::Draw(float camera_work) const
{
	DATA draw_location = { location.x + camera_work, location.y };

	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_WIDTH + radius.x))//��ʓ��Ƀu���b�N������ꍇ
	{
		DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0xFFFFFF, TRUE);
	}
}