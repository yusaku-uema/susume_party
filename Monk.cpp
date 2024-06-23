#include"DxLib.h"
#include"Monk.h"

Monk::Monk(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager) : PlayerBase(location,60,60,5, PLAYER_JOB::MONK)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->enemy_manager = enemy_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Monk/walk.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
	if (LoadDivGraph("image/Player/Monk/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Monk/wait.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
	if ((weapon_image = LoadGraph("image/Player/Monk/weapon.png")) == -1)throw("image/Player/Monk/weapon.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
}

Monk::~Monk()
{

}

void Monk::SpecialSkill()
{
	if (mp >= 10)
	{
		mp -= 10;
		player_manager->AddPlayerHp(25);
	}	
}