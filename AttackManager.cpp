#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager) : 
    stage(stage), player_manager(player_manager), enemy_manager(enemy_manager)
{
    OutputDebugString("AttackManagerコンストラクタ呼ばれました。\n");
}

AttackManager::~AttackManager()
{
    player_attack.clear();
    player_attack.shrink_to_fit();

    enemy_attack.clear();
    enemy_attack.shrink_to_fit();

    OutputDebugString("AttackManagerデストラクタが呼ばれました。\n");
}

void AttackManager::Update(float delta_time)
{
    //プレイヤーの攻撃の更新
    for (int i = 0; i < player_attack.size(); i++)
    {
        if (player_attack[i].Update(delta_time, nullptr, enemy_manager))//攻撃の更新
        {
            player_attack.erase(player_attack.begin() + i);//攻撃を消す
            i--;
        }
    }

    //敵の攻撃の更新
    for (int i = 0; i < enemy_attack.size(); i++)
    {
        if (enemy_attack[i].Update(delta_time, player_manager, nullptr))//攻撃の更新
        {
            enemy_attack.erase(enemy_attack.begin() + i);//攻撃を消す
            i--;
        }
    }
}


////////敵の攻撃の追加/////////////
void AttackManager::AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
    enemy_attack.emplace_back(stage, location, size, speed, duration_time, attack_power, attack_image);
}

////////プレイヤーの攻撃の追加//////////////
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
    //プレイヤー攻撃の表示
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].Draw();

    //敵攻撃の表示
    for (int i = 0; i < enemy_attack.size(); i++)enemy_attack[i].Draw();
}