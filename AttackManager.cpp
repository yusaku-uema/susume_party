#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager) : 
    stage(stage), player_manager(player_manager), enemy_manager(enemy_manager)
{
    for (int i = 0; i < ATTACK_TYPE_NUM; i++)
    {
        for (int j = 0; j < 10; j++)attack_image[i][j] = NULL;
    }

    if (LoadDivGraph("image/Effect/bigexplosion.png", 8, 8, 1, 48, 48, attack_image[ATTACK_TYPE::BIG_EXPLOSION]) == -1)throw("image/Effect/bigexplosion.png���ǂݍ��߂܂���\n");
    if (LoadDivGraph("image/Effect/explosion.png", 5, 5, 1, 24, 24, attack_image[ATTACK_TYPE::EXPLOSION]) == -1)throw("image/Effect/explosion.png���ǂݍ��߂܂���\n");
    if (LoadDivGraph("image/Effect/smallexplosion.png", 4, 4, 1, 16, 16, attack_image[ATTACK_TYPE::SMALL_EXPLOSION]) == -1)throw("image/Effect/smallexplosion.png���ǂݍ��߂܂���\n");
    if (LoadDivGraph("image/Effect/slashing.png", 5, 5, 1, 64, 64, attack_image[ATTACK_TYPE::SLASHING]) == -1)throw("image/Effect/slashing.png���ǂݍ��߂܂���\n");

    if (LoadDivGraph("image/Effect/spinslash.png", 2, 2, 1, 32, 24, attack_image[ATTACK_TYPE::SPIN_SLASH]) == -1)throw("image/Effect/spinslash.png���ǂݍ��߂܂���\n");
    if (LoadDivGraph("image/Effect/fireball.png", 4, 4, 1, 24, 24, attack_image[ATTACK_TYPE::FIRE_BALL]) == -1)throw("image/Effect/fireball.png���ǂݍ��߂܂���\n");


    OutputDebugString("AttackManager�R���X�g���N�^�Ă΂�܂����B\n");
}

AttackManager::~AttackManager()
{
    player_attack.clear();
    player_attack.shrink_to_fit();

    enemy_attack.clear();
    enemy_attack.shrink_to_fit();

    for (int i = 0; i < ATTACK_TYPE_NUM; i++)
    {
        for (int j = 0; j < 10; j++)DeleteGraph(attack_image[i][j]);
    }

    OutputDebugString("AttackManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void AttackManager::Update(float delta_time)
{
    //�v���C���[�̍U���̍X�V
    for (int i = 0; i < player_attack.size(); i++)
    {
        if (player_attack[i].Update(delta_time, stage, nullptr, enemy_manager))//�U���̍X�V
        {
            player_attack.erase(player_attack.begin() + i);//�U��������
            i--;
        }
    }

    //�G�̍U���̍X�V
    for (int i = 0; i < enemy_attack.size(); i++)
    {
        if (enemy_attack[i].Update(delta_time, stage, player_manager, nullptr))//�U���̍X�V
        {
            enemy_attack.erase(enemy_attack.begin() + i);//�U��������
            i--;
        }
    }
}

//�ǐՃL���������������̏���
void AttackManager::DeleteTargetPointer(BoxCollider* target)
{
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].DeleteTargetPointer(target);
}


////////�G�̍U���̒ǉ�/////////////
void AttackManager::AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    enemy_attack.emplace_back(location, size, speed, nullptr, duration_time, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

////////�v���C���[�̍U���̒ǉ�//////////////
void AttackManager::AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    class BoxCollider* enemy = enemy_manager->GetEnemyData(0);

    player_attack.emplace_back(location, size, speed, enemy, 999, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

void AttackManager::SetPointer(class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
}

void AttackManager::Draw() const
{
    //�v���C���[�U���̕\��
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].Draw(stage->GetCameraWork());

    //�G�U���̕\��
    for (int i = 0; i < enemy_attack.size(); i++)enemy_attack[i].Draw(stage->GetCameraWork());
}