#include"DxLib.h"
#include"Hero.h"

Hero::Hero() : PlayerBase(PLAYER_JOB::HERO)
{
	if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Hero/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Hero/wait.png���ǂݍ��߂܂���\n");
	if((weapon_image = LoadGraph("image/Player/Hero/weapon.png")) == -1)throw("image/Player/Hero/weapon.png���ǂݍ��߂܂���\n");

}

Hero::~Hero()
{

}

//���Z
void Hero::SpecialSkill()
{
    if (is_facing_left)
    {
        //���ɍU��
        attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { -8.0f,0.0f }, nullptr, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
    }
    else
    {
        //�E�ɍU��
        attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { 8.0f,0.0f }, nullptr, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
    }
}