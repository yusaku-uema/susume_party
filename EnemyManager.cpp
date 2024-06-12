#include"DxLib.h"
#include"EnemyManager.h"
#include"Key.h"

//ザコ敵
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"Fairy.h"

//ボス
#include"BlackMage.h"

#define DRAW_ARROW_TIME 2.0f//プレイヤーを指す矢印の表示時間

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, int enemy_type, DATA location):
    stage(stage), player_manager(player_manager), attack_manager(attack_manager)
{
    SpawnEnemy(enemy_type,location);
    OutputDebugString("EnemyManagerコンストラクタ呼ばれました。\n");
}



EnemyManager::~EnemyManager()
{
    for (int i = 0; i < enemy.size(); i++)delete enemy[i];
    enemy.clear();
    enemy.shrink_to_fit();

    OutputDebugString("EnemyManagerデストラクタが呼ばれました。\n");
}

void EnemyManager::Update(float delta_time)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update();

        //死んだ場合
        if (enemy[i]->GetIsDead())
        {
            delete enemy[i];
            enemy.erase(enemy.begin() + i);//攻撃を消す
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
