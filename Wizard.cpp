#include"DxLib.h"
#include"Wizard.h"

Wizard::Wizard() : PlayerBase(PLAYER_JOB::WIZARD)
{
	if (LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("image/Wizard/Hero/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("image/Player/Wizard/wait.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("image/Wizard/Hero/wait.png���ǂݍ��߂܂���\n");
	if ((weapon_image = LoadGraph("image/Player/Wizard/weapon.png")) == -1)throw("image/Player/Wizard/weapon.png���ǂݍ��߂܂���\n");
}

Wizard::~Wizard()
{

}

//���Z
void Wizard::SpecialSkill()
{
	BoxCollider* enemy =  nullptr;
	float min_distance = 500.0f;

	for (int i = 0; i < enemy_manager->GetEnemyNum(); i++)
	{
		float dx = location.x - enemy_manager->GetEnemyData(i)->GetLocation().x;
		float dy = location.y - enemy_manager->GetEnemyData(i)->GetLocation().y;
		float distance = sqrt(dx * dx + dy * dy); // ���[�N���b�h�����̌v�Z�i�����������j

		if (distance < min_distance)
		{
			min_distance = distance;
			enemy = enemy_manager->GetEnemyData(i);
		}
	}

	if (is_facing_left)
	{
		//���ɍU��
		attack_manager->AddPlayerAttack(location, { 10.0f,15.0f }, { -7.0f,0.0f }, enemy, 100.0f, 3, ATTACK_TYPE::FIRE_BALL, 4.0f);
	}
	else
	{
		//�E�ɍU��
		attack_manager->AddPlayerAttack(location, { 10.0f,15.0f }, { 7.0f,0.0f }, enemy, 100.0f, 3, ATTACK_TYPE::FIRE_BALL, 4.0f);
	}
}