#include"DxLib.h"
#include"AttackManager.h"

AttackManager::AttackManager()
{
    for (int i = 0; i < ATTACK_TYPE_NUM; i++)
    {
        for (int j = 0; j < 10; j++)attack_image[i][j] = NULL;
    }

    if (LoadDivGraph("image/Effect/bigexplosion.png", 8, 8, 1, 48, 48, attack_image[ATTACK_TYPE::BIG_EXPLOSION]) == -1)throw("image/Effect/bigexplosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/explosion.png", 5, 5, 1, 24, 24, attack_image[ATTACK_TYPE::EXPLOSION]) == -1)throw("image/Effect/explosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/smallexplosion.png", 4, 4, 1, 16, 16, attack_image[ATTACK_TYPE::SMALL_EXPLOSION]) == -1)throw("image/Effect/smallexplosion.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/slashing.png", 5, 5, 1, 64, 64, attack_image[ATTACK_TYPE::SLASHING]) == -1)throw("image/Effect/slashing.pngが読み込めません\n");

    if (LoadDivGraph("image/Effect/spinslash.png", 2, 2, 1, 32, 24, attack_image[ATTACK_TYPE::SPIN_SLASH]) == -1)throw("image/Effect/spinslash.pngが読み込めません\n");
    if (LoadDivGraph("image/Effect/fireball.png", 4, 4, 1, 24, 24, attack_image[ATTACK_TYPE::FIRE_BALL]) == -1)throw("image/Effect/fireball.pngが読み込めません\n");

    OutputDebugString("AttackManagerコンストラクタ呼ばれました。\n");
}

void AttackManager::Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
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

//追跡キャラが消えた時の処理
void AttackManager::DeleteTargetPointer(BoxCollider* target)
{
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].DeleteTargetPointer(target);
}

////////敵の攻撃の追加/////////////
void AttackManager::AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    enemy_attack.emplace_back(location, size, speed, nullptr,true,true, duration_time, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

////////プレイヤーの攻撃の追加//////////////
void AttackManager::AddPlayerAttack(DATA location, DATA size, DATA speed, class BoxCollider* bc,bool delete_hit_stage,bool delete_hit_chara, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size)
{
    player_attack.emplace_back(location, size, speed, bc, delete_hit_stage, delete_hit_chara, duration_time, attack_power, attack_image[attack_type], attack_image_num[attack_type], image_size);
}

void AttackManager::Draw() const
{
    //プレイヤー攻撃の表示
    for (int i = 0; i < player_attack.size(); i++)player_attack[i].Draw(stage->GetCameraWork());

    //敵攻撃の表示
    for (int i = 0; i < enemy_attack.size(); i++)enemy_attack[i].Draw(stage->GetCameraWork());
}