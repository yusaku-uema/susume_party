#include "Fairy.h"
#define FAIRY_SIZE 64


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Fairy::Fairy() : CharacterBase({ 1400.0f, 50.0f }, { FAIRY_SIZE, FAIRY_SIZE }, 20, 10, 5, 5)
{

}


//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Fairy::~Fairy()
{

}


//-----------------------------------
//�X�V����
//-----------------------------------
void Fairy::Update(float delta_time, Stage* stage, PlayerManager* player)
{

}


//-----------------------------------
//�`��
//-----------------------------------
void Fairy::Draw(float camera_work) const
{

}


//-----------------------------------
//�ړ�
//-----------------------------------
void Fairy::Move(Stage* stage, PlayerManager* player)
{

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
