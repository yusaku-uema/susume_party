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

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, int enemy_type, DATA location):
    stage(stage), player_manager(player_manager), attack_manager(attack_manager)
{
    SpawnEnemy(enemy_type,location);
    OutputDebugString("EnemyManager�R���X�g���N�^�Ă΂�܂����B\n");
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
            delete enemy[i];
            enemy.erase(enemy.begin() + i);//�U��������
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

void EnemyManager::Draw() const
{
    for (int i = 0; i < enemy.size(); i++)enemy[i]->Draw();
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
