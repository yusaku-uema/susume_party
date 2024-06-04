#pragma once
#include"Attack.h"
#include"Stage.h"

#define ATTACK_TYPE_NUM 4//攻撃種類（アニメーションの種類）

////攻撃の種類
enum ATTACK_TYPE
{
    BIG_EXPLOSION,//大爆発
    EXPLOSION,//爆発
    SMALL_EXPLOSION,//小爆発
    SPIN_SLASH//回転斬り
};

class AttackManager
{
private:
    std::vector<class Attack>player_attack;
    std::vector<class Attack>enemy_attack;

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;

    int attack_image[ATTACK_TYPE_NUM][10];//攻撃画像
    const int attack_image_num[ATTACK_TYPE_NUM] = {8, 5, 4, 2};//攻撃画像の数
   
public:

    AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    ~AttackManager();

    //敵の攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type);
    //プレイヤーの攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type);

    void Update(float delta_time);
    void Draw() const;

    void SetPointer(class PlayerManager* player_manager, class EnemyManager* enemy_manager);
};