#include"DxLib.h"
#include"Warrior.h"

Warrior::Warrior() : PlayerBase(PLAYER_JOB::WARRIOR)
{
	if (LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Warrior/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Warrior/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Warrior/wait.png���ǂݍ��߂܂���\n");
	if ((weapon_image = LoadGraph("image/Player/Warrior/weapon.png")) == -1)throw("image/Player/Warrior/weapon.png���ǂݍ��߂܂���\n");
}

Warrior::~Warrior()
{

}