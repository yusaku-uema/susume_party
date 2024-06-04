#include"DxLib.h"
#include"EnemyManager.h"

//�U�R�G
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//�{�X
#include"BlackMage.h"

//#include"Stage.h"

#define DRAW_ARROW_TIME 2.0f//�v���C���[���w�����̕\������

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager)
{
    enemy[0] = new Slime(stage, player_manager, attack_manager);
    enemy[1] = new Bird(stage, player_manager, attack_manager);
    enemy[2] = new Flower(stage, player_manager, attack_manager);
    enemy[3] = new Fairy(stage, player_manager, attack_manager);
    enemy[4] = new BlackMage(stage, player_manager, attack_manager);

    OutputDebugString("EnemyManager�R���X�g���N�^�Ă΂�܂����B\n");
}

EnemyManager::~EnemyManager()
{
    for (int i = 0; i < ENEMY_NUM; i++)delete enemy[i];

    OutputDebugString("EnemyManager�f�X�g���N�^���Ă΂�܂����B\n");
}

void EnemyManager::Update(float delta_time)
{
    for (int i = 0; i < ENEMY_NUM; i++)enemy[i]->Update();
}

bool EnemyManager::CheckHitDamage(class BoxCollider* bc, int attack_power)
{
    for (int i = 0; i < ENEMY_NUM; i++)
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
    for (int i = 0; i < ENEMY_NUM; i++)enemy[i]->Draw();
}