#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : PlayerBase(PLAYER_JOB::WIZARD)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Wizard/Hero/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Wizard/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Wizard/Hero/wait.png���ǂݍ��߂܂���\n");
	if ((weapon_image = LoadGraph("image/Player/Wizard/weapon.png")) == -1)throw("image/Player/Wizard/weapon.png���ǂݍ��߂܂���\n");
}

Wizard::~Wizard()
{

}