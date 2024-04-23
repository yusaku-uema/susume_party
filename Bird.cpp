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

}

Bird::~Bird()
{
	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
}

void Bird::Update(float delta_time, Stage* stage)
{
	//y���W�̍X�V
	if ((speed.y += GRAVITY) > FALL_SPEED)speed.y = FALL_SPEED;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�
	
	if ((distance_moved += UP_SPEED) > FALL_MAX)distance_moved=0, move_up = !move_up, speed.y=0; //������

	if (move_up) //�t���O��TRUE�̏ꍇ�A�㏸����
	{
		location.y -= speed.y;
	}
	else
	{
		location.y += speed.y;
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




}

void Bird::Draw() const
{
	DrawBox(location.x - radius.x, location.y - radius.y, location.x + radius.x, location.y + radius.y, 0x00ffff, TRUE);
}