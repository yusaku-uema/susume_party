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

	start_attack = false;
	move_up = false;
	move_left = true;

}

Bird::~Bird()
{
	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
}

void Bird::Update(float delta_time, Stage* stage, class PlayerManager* player)
{

	if (start_attack)
	{
		
	}
	else
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

		//�擪�v���C���[�Ƃ̋�����300�ȉ��Ȃ�U���J�n
		if (CalculateDistance(player) < 300)
		{
			start_attack = true;
		}
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

float Bird::CalculateDistance(PlayerManager* player)
{
	float dx = player->GetPlayerLocation().x - this->GetLocation().x;
	float dy = player->GetPlayerLocation().y - this->GetLocation().y;
	float distance = sqrt(dx * dx + dy * dy); // ���[�N���b�h�����̌v�Z�i�����������j

	return distance;
}
