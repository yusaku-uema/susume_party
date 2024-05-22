#include "BlackMage.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BLACKMAGE_SIZE 132

BlackMage::BlackMage() : CharacterBase({ 300.0f, 300.0f }, { BLACKMAGE_SIZE, BLACKMAGE_SIZE }, 20, 10, 5, 5)
{
	OutputDebugString("�����m�R���X�g���N�^�Ă΂�܂����B\n");

	if (LoadDivGraph("image/Enemy/fairy.png", 12, 12, 1, 64, 64, blackmage_image) == -1)throw("�����m�i�{�X�j���Ǎ��ݎ��s\n");


	image_type = 0;
	animation_time = 0;

	time = 0;

	attack_speed = 0;
	distance_moved = 0;


	move_left = true;
	direction = true;
	lock_on = false;


	state = BLACKMAGE_STATE::NORMAL;
}

BlackMage::~BlackMage()
{

}

void BlackMage::Update(float delta_time, Stage* stage, PlayerManager* player)
{

}

void BlackMage::Draw(float camera_work) const
{

}

void BlackMage::Move(Stage* stage, PlayerManager* player)
{

}

void BlackMage::Standby(PlayerManager* player)
{

}

void BlackMage::Attack(Stage* stage, PlayerManager* player, float delta_time)
{

}

float BlackMage::CalculateDistance(PlayerManager* player)
{
	return 0.0f;
}
