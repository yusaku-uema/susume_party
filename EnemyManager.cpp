#include"DxLib.h"
#include"EnemyManager.h"
#include"Key.h"

//�U�R�G
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//�{�X
#include"BlackMage.h"

#define DRAW_ARROW_TIME 2.0f//�v���C���[���w�����̕\������

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager):
    stage(stage), player_manager(player_manager), attack_manager(attack_manager)
{
    OutputDebugString("EnemyManager�R���X�g���N�^�Ă΂�܂����B\n");
    SetEnemy();
}

EnemyManager::~EnemyManager()
{
    for (int i = 0; i < enemy.size(); i++)delete enemy[i];
    enemy.clear();
    enemy.shrink_to_fit();

    OutputDebugString("EnemyManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void EnemyManager::Update(float delta_time)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update();

        //���񂾏ꍇ
        if (enemy[i]->GetIsDead())
        {
            attack_manager->DeleteTargetPointer(enemy[i]);
            delete enemy[i];
            enemy.erase(enemy.begin() + i);//�G������
            i--;
        }
    }
}

bool EnemyManager::CheckHitDamage(class BoxCollider* bc, int attack_power)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        if (enemy[i]->HitBox(bc))
        {
            enemy[i]->HitDamege(bc, attack_power);
            return true;
        }
    }
    return false;
}

class BoxCollider* EnemyManager::GetEnemyData(int enemy_num)const
{
    return enemy[enemy_num];
}

int EnemyManager::GetEnemyNum()const
{
    return enemy.size();
}

void EnemyManager::Draw() const
{
    for (int i = 0; i < enemy.size(); i++)
    {
        DrawFormatString(enemy[i]->GetLocation().x + stage->GetCameraWork(), enemy[i]->GetLocation().y - 50, 0xffffff, "%d", i);
        enemy[i]->Draw();
    }
}

void EnemyManager::SpawnEnemy(int enemy_type, DATA location)
{
    switch (enemy_type)
    {
    case ENEMY_TYPE::BIRD:
        enemy.emplace_back(new Bird(stage, player_manager, attack_manager,location));
        break;
    case ENEMY_TYPE::FAIRY:
        enemy.emplace_back(new Fairy(stage, player_manager, attack_manager, location));
        break;
    case ENEMY_TYPE::FLOWER:
        enemy.emplace_back(new Flower(stage, player_manager, attack_manager, location));
        break;
    case ENEMY_TYPE::SLIME:
        enemy.emplace_back(new Slime(stage, player_manager, attack_manager, location));
        break;
    case ENEMY_TYPE::BLACKMAGE:
        enemy.emplace_back(new BlackMage(stage, player_manager, attack_manager, location));
        break;

    default:
        break;
    }
}

void EnemyManager::SetEnemy()
{
    FILE* enemy_data = nullptr;//�X�e�[�W�ǂݍ���

    errno_t error_enemy_data = fopen_s(&enemy_data, "data/enemyplacement.txt", "r");
    if (error_enemy_data != 0)throw("data/enemyplacement.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N


    //�G�l�~�[��z�u����
    for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//�c�̌J��Ԃ�
    {
        for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//���̌J��Ԃ�
        {
            //�G�l�~�[�̎��
            int enemy_type;
            fscanf_s(enemy_data, "%d", &enemy_type);

            //�G�l�~�[�̐���
            if (enemy_type != -1)
            {
                DATA location = { j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) };
                
                SpawnEnemy(enemy_type, location);
                
            }
        }
    }
    fclose(enemy_data);
}
