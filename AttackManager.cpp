#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager) : 
    stage(stage), player_manager(player_manager), enemy_manager(enemy_manager)
{
    for (int i = 0; i < ATTACK_TYPE_NUM; i++)
    {
        for (int j = 0; j < 10; j++)attack_image[i][j] = NULL;
    }

    if (LoadDivGraph("image/Effect/big_explosion.png", 8, 8, 1, 48, 48, attack_image[ATTACK_TYPE::BIG_EXPLOSION]) == -1)throw("image/Effect/big_explosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/explosion.png", 5, 5, 1, 24, 24, attack_image[ATTACK_TYPE::EXPLOSION]) == -1)throw("image/Effect/explosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/small_explosion.png", 4, 4, 1, 16, 16, attack_image[ATTACK_TYPE::SMALL_EXPLOSION]) == -1)throw("image/Effect/small_explosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/spin_slash.png", 2, 2, 1, 32, 24, attack_image[ATTACK_TYPE::SPIN_SLASH]) == -1)throw("image/Effect/spin_slash.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/fireball.png", 4, 4, 1, 24, 24, attack_image[ATTACK_TYPE::FIRE_BALL]) == -1)throw("image/Effect/fireball.pngが読み込めません\n");


    OutputDebugString("AttackManagerコンストラクタ呼ばれました。\n");
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

    OutputDebugString("AttackManagerデストラクタが呼ばれました。\n");
}

void AttackManager::Update(float delta_time)
{
    //プレイヤーの攻撃の更新
    for (int i = 0; i < player_attack.size(); i++)
    {
        if (player_attack[i].Update(delta_time, stage, nullptr, enemy_manager))//攻撃の更新
        {
            player_attack.erase(player_attack.begin() + i);//攻撃を消す
            i--;
        }
    }

    //敵の攻撃の更新
    for (int i = 0; i < enemy_attack.size(); i++)
    {
        if (enemy_attack[i].Update(delta_time, stage, player_manager, nullptr))//攻撃の更新
        {
            enemy_attack.erase(enemy_attack.begin() + i);//攻撃を消す
            i--;
        }
    }
}


////////敵の攻撃の追加/////////////
void AttackManager::AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    enemy_attack.emplace_back(location, size, speed, duration_time, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

////////プレイヤーの攻撃の追加//////////////
void AttackManager::AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    player_attack.emplace_back(location, size, speed, duration_time, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

void AttackManager::SetPointer(class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
}

void AttackManager::Draw() const
{
    //プレイヤー攻撃の表示
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].Draw(stage->GetCameraWork());

    //敵攻撃の表示
    for (int i = 0; i < enemy_attack.size(); i++)enemy_attack[i].Draw(stage->GetCameraWork());
}