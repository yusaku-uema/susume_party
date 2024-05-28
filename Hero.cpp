#include"DxLib.h"
#include"Hero.h"

Hero::Hero(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) : PlayerBase(PLAYER_JOB::HERO)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Hero/walk.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
	if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Hero/wait.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ\n");
}

Hero::~Hero()
{

}