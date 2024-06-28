//#include"DxLib.h"
//#include"Bird.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//#define BIRD_SIZE 9.5f//�T�C�Y
//#define WALK_SPEED 1.5f//1�t���[���̍ő呬
//#define ACCELERATION 0.1f//�ړ����̉���
//#define UP_SPEED 0.1f //�㏸�A���~�̑��x
//#define FALL_MAX 7.5  //�㏸�A���~�̏��
//#define SEARCH_RANGE 300 //��틗��
//#define IMAGE_SWITCHING_TIMING 12 //�摜�ؑփ^�C�~���O
//#define WAITING_TIME_FOR_ATTACK 60 //�U���ҋ@���ԁi�U���^�C�~���O�j
//#define MAX_HP 10
//
////-----------------------------------
////�R���X�g���N�^
////-----------------------------------
//Bird::Bird(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location) : EnemyBase()
//{
//	this->stage = stage;
//	this->player_manager = player_manager;
//	this->attack_manager = attack_manager;
//
//	OutputDebugString("Bird�R���X�g���N�^�Ă΂�܂����B\n");
//
//	if (LoadDivGraph("image/Enemy/Bird.png", 11, 11, 1, 80, 80, bird_image) == -1)throw("�o�[�h�摜�Ǎ��ݎ��s\n");
//
//	image_type = 0;
//	animation_time = 0;
//
//	time = 0;
//
//	attack_speed = 0;
//	distance_moved = 0;
//
//	angle = 0;
//
//	move_up = false;
//	move_left = false;
//	direction = true;
//	lock_on = false;
//
//	state = BIRD_STATE::NORMAL;
//
//
//	this->location = location;
//	spawn_location = location;
//
//	////�e�X�g ���W
//	//this->location = { 900.0f, 250.0f };
//	this->radius = { BIRD_SIZE ,BIRD_SIZE };
//	this->hp = MAX_HP;
//}
//
////-----------------------------------
////�f�X�g���N�^
////-----------------------------------
//Bird::~Bird()
//{
//	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
//	for (int i = 0; i < 11; i++)
//	{
//		DeleteGraph(bird_image[i]);
//	}
//}
//
//
////-----------------------------------
//// �X�V����
////-----------------------------------
//void Bird::Update()
//{
//	//�A�j���[�V�������ԍX�V
//	++animation_time;
//
//	if (ScopeoOfActivity(stage->GetCameraWork()))
//	{
//		move_left=!move_left;
//	}
//	switch (state)
//	{
//	case BIRD_STATE::NORMAL: //�ʏ�ړ�
//		Move();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 3)
//			{
//				image_type = 0;
//			}
//		}
//
//		break;
//	case BIRD_STATE::STANDBY: //�U�������i�ҋ@�j
//		Standby();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 10)
//			{
//				image_type = 7;
//			}
//		}
//
//		break;
//	case BIRD_STATE::ATTACK: //�U��
//		Attack();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 6)
//			{
//				image_type = 4;
//			}
//		}
//
//		break;
//	case BIRD_STATE::RETURN:
//		Return();
//
//		if (animation_time % IMAGE_SWITCHING_TIMING == 0)
//		{
//			if (++image_type > 3)
//			{
//				image_type = 0;
//			}
//		}
//
//		break;
//	}
//}
//
////-----------------------------------
//// �`��
////-----------------------------------
//void Bird::Draw() const
//{
//	DATA draw_location = { location.x + stage->GetCameraWork(), location.y };
//
//	if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))//��ʓ��Ƀu���b�N������ꍇ
//	{
//		if (state == BIRD_STATE::ATTACK || state == BIRD_STATE::STANDBY)
//		{
//			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, direction);
//		}
//		else
//		{
//			DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, bird_image[image_type], TRUE, !move_left);
//		}
//		//DrawFormatString(draw_location.x, draw_location.y - 100, 0xffffff, "	�p�x =%f", angle);
//		////DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x00ffff, FALSE);
//
//		DrawHPBar(MAX_HP);
//	}
//}
//
//
////-----------------------------------
//// �ʏ�ړ�(�E�ɓ��������ɓ�����)
////-----------------------------------
//void Bird::Move()
//{
//
//	//x���W�̍X�V
//	if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�
//
//	if (move_left)
//	{
//		location.x -= speed.x;
//	}
//	else
//	{
//		location.x += speed.x;
//	}
//
//	if (stage->HitBlock(this))
//	{
//		while (stage->HitBlock(this)) //�i�s�����Ƃ͋t�ɐi�ݓ����蔻�肩��E�o
//		{
//
//			if (move_left)
//			{
//				location.x += speed.x;
//			}
//			else
//			{
//				location.x -= speed.x;
//			}
//		}
//
//		move_left = !move_left;
//	}
//
//	//�擪�v���C���[�Ƃ̋�����SEARCH_RANGE�ȉ��Ȃ�U������
//	if (CalculateDistance() < SEARCH_RANGE)
//	{
//		state = BIRD_STATE::STANDBY;
//		image_type = 7;
//	}
//
//
//}
//
////-----------------------------------
//// �U������(�ҋ@)
////-----------------------------------
//void Bird::Standby()
//{
//
//	//�擪�v���C���[�Ƃ̋�����SEARCH_RANGE�ȉ��Ȃ�U���J�n
//	if (CalculateDistance() < SEARCH_RANGE)
//	{
//		if (++time % WAITING_TIME_FOR_ATTACK == 0)
//		{
//			state = BIRD_STATE::ATTACK;
//			player_location = player_manager->GetPlayerData()->GetLocation();
//			old_location = location;
//			time = 0;
//		}
//	}
//	else //���������ꂽ��ʏ�ړ���
//	{
//		state = BIRD_STATE::NORMAL;
//		time = 0;
//	}
//
//}
//
////-----------------------------------
//// �U�����̈ړ�
////-----------------------------------
//void Bird::Attack()
//{
//	CalculateDistance();
//
//	dx = player_location.x - location.x;
//	dy = player_location.y - location.y;
//	distance = sqrtf(dx * dx + dy * dy);
//
//	angle = atan2(dy, dx) * 180 / M_PI;
//
//	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�
//
//	if (stage->HitBlock(this))
//	{
//		state = BIRD_STATE::RETURN;
//		attack_speed = 0;
//		lock_on = false;
//	}
//	else
//	{
//		if (distance > 5)
//		{
//			location.x += (dx / distance) * attack_speed;
//			location.y += (dy / distance) * attack_speed;
//		}
//		else
//		{
//			state = BIRD_STATE::RETURN;
//			attack_speed = 0;
//		}
//	}
//
//	if (player_manager->CheckHitDamage(this, 5))
//	{
//		state = BIRD_STATE::RETURN;
//		attack_speed = 0;
//	}
//}
//
//
////-----------------------------------
//// �ҋ@���Ă����ʒu�ɖ߂�
////-----------------------------------
//void Bird::Return()
//{
//	float dx = old_location.x - location.x;
//	float dy = old_location.y - location.y;
//	float distance = sqrtf(dx * dx + dy * dy);
//
//
//	if ((attack_speed += UP_SPEED) > FALL_MAX)attack_speed = FALL_MAX;//�X�s�[�h�ɉ����x�𑫂��Ă����āA�ő�l�ɒB������Œ�
//
//	if (distance >= 5)
//	{
//		location.x += (dx / distance) * FALL_MAX;
//		location.y += (dy / distance) * FALL_MAX;
//	}
//	else
//	{
//		attack_speed = 0;
//		state = BIRD_STATE::NORMAL;
//	}
//}
//
////-----------------------------------
//// �擪�ɂ���v���C���[�Ƃ̓����蔻��
////-----------------------------------
//float Bird::CalculateDistance() {
//	float dx = player_manager->GetPlayerData()->GetLocation().x - this->GetLocation().x;
//	float dy = player_manager->GetPlayerData()->GetLocation().y - this->GetLocation().y;
//	float distance = sqrt(dx * dx + dy * dy); // ���[�N���b�h�����̌v�Z�i�����������j
//
//	float angle = atan2(dy, dx) * 180 / M_PI;
//	if (angle >= -45 && angle <= 85)
//	{
//		direction = true;
//	}
//	else
//	{
//		direction = false;
//	}
//
//	return distance;
//
//
//}
