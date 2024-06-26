#include"DxLib.h"
#include"Hero.h"

Hero::Hero(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager) : PlayerBase(location,80,30,10, PLAYER_JOB::HERO)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
    this->attack_manager = attack_manager;

	if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Player/Hero/walk.pngが読み込めません\n");
	if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Player/Hero/wait.pngが読み込めません\n");
	if((weapon_image = LoadGraph("image/Player/Hero/weapon.png")) == -1)throw("image/Player/Hero/weapon.pngが読み込めません\n");

}

Hero::~Hero()
{

}

//特技
void Hero::SpecialSkill()
{
    if (mp >= 3)
    {
        mp -= 3;

        if (is_facing_left)
        {
            //左に攻撃
            attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { -8.0f,0.0f }, nullptr,true,true, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
        }
        else
        {
            //右に攻撃
            attack_manager->AddPlayerAttack(location, { 10.0f,10.0f }, { 8.0f,0.0f }, nullptr,true,true, 5.0f, 3, ATTACK_TYPE::FIRE_BALL, 2.0f);
        }
    }
}