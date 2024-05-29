#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager) : 
    stage(stage), player_manager(player_manager), enemy_manager(enemy_manager)
{
    OutputDebugString("AttackManager�R���X�g���N�^�Ă΂�܂����B\n");
}

AttackManager::~AttackManager()
{
    player_attack.clear();
    player_attack.shrink_to_fit();

    enemy_attack.clear();
    enemy_attack.shrink_to_fit();

    OutputDebugString("AttackManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void AttackManager::Update(float delta_time)
{
    //�v���C���[�̍U���̍X�V
    for (int i = 0; i < player_attack.size(); i++)
    {
        if (player_attack[i].Update(delta_time, nullptr, enemy_manager))//�U���̍X�V
        {
            player_attack.erase(player_attack.begin() + i);//�U��������
            i--;
        }
    }

    //�G�̍U���̍X�V
    for (int i = 0; i < enemy_attack.size(); i++)
    {
        if (enemy_attack[i].Update(delta_time, player_manager, nullptr))//�U���̍X�V
        {
            enemy_attack.erase(enemy_attack.begin() + i);//�U��������
            i--;
        }
    }
}


////////�G�̍U���̒ǉ�/////////////
void AttackManager::AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    enemy_attack.emplace_back(stage, location, size, speed, duration_time, attack_power, attack_image);
}

////////�v���C���[�̍U���̒ǉ�//////////////
void AttackManager::AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    player_attack.emplace_back(stage, location, size, speed, duration_time, attack_power, attack_image);
}

void AttackManager::SetPointer(class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
}

void AttackManager::Draw() const
{
    //�v���C���[�U���̕\��
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].Draw();

    //�G�U���̕\��
    for (int i = 0; i < enemy_attack.size(); i++)enemy_attack[i].Draw();
}