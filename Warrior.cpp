#include"DxLib.h"
#include"Warrior.h"

Warrior::Warrior(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager) : PlayerBase(location, PLAYER_JOB::WARRIOR)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->enemy_manager = enemy_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Warrior/walk.pngが読み込めません\n");
	if (LoadDivGraph("image/Player/Warrior/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Warrior/wait.pngが読み込めません\n");
	if ((weapon_image = LoadGraph("image/Player/Warrior/weapon.png")) == -1)throw("image/Player/Warrior/weapon.pngが読み込めません\n");
}

Warrior::~Warrior()
{

}