#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard(DATA location, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager) : PlayerBase(location, 50,70,5,PLAYER_JOB::WIZARD)
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->enemy_manager = enemy_manager;
	this->attack_manager = attack_manager;

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
	if (mp >= 5)
	{
		mp -= 5;

		BoxCollider* enemy = nullptr;
		float min_distance = 500.0f;

		for (int i = 0; i < enemy_manager->GetEnemyNum(); i++)
		{
			float dx = location.x - enemy_manager->GetEnemyData(i)->GetLocation().x;
			float dy = location.y - enemy_manager->GetEnemyData(i)->GetLocation().y;
			float distance = sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）

			if (distance < min_distance)
			{
				min_distance = distance;
				enemy = enemy_manager->GetEnemyData(i);
			}
		}

		if (is_facing_left)
		{
			//左に攻撃
			attack_manager->AddPlayerAttack(location, { 8.0f,8.0f }, { -7.0f,0.0f }, enemy,true,true, 100.0f, 3, ATTACK_TYPE::FIRE_BALL, 4.0f);
		}
		else
		{
			//右に攻撃
			attack_manager->AddPlayerAttack(location, { 8.0f,8.0f }, { 7.0f,0.0f }, enemy, true,true,100.0f, 3, ATTACK_TYPE::FIRE_BALL, 4.0f);
		}
	}
}