#include"DxLib.h"
#include"Warrior.h"

Warrior::Warrior(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager) : PlayerBase(location,100,20,15, PLAYER_JOB::WARRIOR)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->enemy_manager = enemy_manager;
	this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Warrior/walk.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
	if (LoadDivGraph("image/Player/Warrior/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Warrior/wait.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
	if ((weapon_image = LoadGraph("image/Player/Warrior/weapon.png")) == -1)throw("image/Player/Warrior/weapon.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ\n");
}

Warrior::~Warrior()
{

}

void Warrior::SpecialSkill()
{
    if (mp >= 4)
    {
        mp -= 4;

        if (is_facing_left)
        {
            //¶‚ÉUŒ‚
            attack_manager->AddPlayerAttack(location, { 50.0f,50.0f }, { -6.0f,0.0f }, nullptr, false, false, 7.0f, 1, ATTACK_TYPE::SPIN_SLASH, 3.0f);
        }
        else
        {
            //‰E‚ÉUŒ‚
            attack_manager->AddPlayerAttack(location, { 50.0f, 50.0f }, { 6.0f,0.0f }, nullptr, false, false, 7.0f, 1, ATTACK_TYPE::SPIN_SLASH, 3.0f);
        }
    }
}