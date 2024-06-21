#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard() : PlayerBase(PLAYER_JOB::WIZARD)
{
	if (LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Wizard/Hero/walk.pngが読み込めません\n");
	if (LoadDivGraph("image/Player/Wizard/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Wizard/Hero/wait.pngが読み込めません\n");
	if ((weapon_image = LoadGraph("image/Player/Wizard/weapon.png")) == -1)throw("image/Player/Wizard/weapon.pngが読み込めません\n");
}

Wizard::~Wizard()
{

}

//特技
void Wizard::SpecialSkill()
{
    BoxCollider* enemy = enemy_manager->GetEnemyData(0);

	attack_manager->AddPlayerAttack(location, { 15.0f,15.0f }, { 0.0f,0.0f }, enemy, 100.0f, 3, ATTACK_TYPE::FIRE_BALL, 4.0f);

}