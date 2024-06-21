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

EnemyManager::EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager):
    stage(stage), player_manager(player_manager), attack_manager(attack_manager)
{
    OutputDebugString("EnemyManagerコンストラクタ呼ばれました。\n");
    SetEnemy();
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
            attack_manager->DeleteTargetPointer(enemy[i]);
            delete enemy[i];
            enemy.erase(enemy.begin() + i);//敵を消す
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
    FILE* enemy_data = nullptr;//ステージ読み込み

    errno_t error_enemy_data = fopen_s(&enemy_data, "data/enemyplacement.txt", "r");
    if (error_enemy_data != 0)throw("data/enemyplacement.txtが読み込めません\n");//エラーチェック


    //エネミーを配置する
    for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//縦の繰り返し
    {
        for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//横の繰り返し
        {
            //エネミーの種類
            int enemy_type;
            fscanf_s(enemy_data, "%d", &enemy_type);

            //エネミーの生成
            if (enemy_type != -1)
            {
                DATA location = { j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) };
                
                SpawnEnemy(enemy_type, location);
                
            }
        }
    }
    fclose(enemy_data);
}
