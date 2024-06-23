#pragma once
#include"Attack.h"
#include"Stage.h"

#define ATTACK_TYPE_NUM 7//攻撃種類（アニメーションの種類）

////攻撃の種類
enum ATTACK_TYPE
{
    NONE,
    BIG_EXPLOSION,//大爆発
    EXPLOSION,//爆発
    SMALL_EXPLOSION,//小爆発
    SLASHING,//斬撃
    SPIN_SLASH,//回転斬り
    FIRE_BALL
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
    const int attack_image_num[ATTACK_TYPE_NUM] = { 0, 8, 5, 4, 5, 2, 1 };//攻撃画像の数
   
public:
    AttackManager();
    ~AttackManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);

    //敵の攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size);
    //プレイヤーの攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddPlayerAttack(DATA location, DATA size, DATA speed, class BoxCollider* bc, bool delete_hit_stage, bool delete_hit_chara, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size);

    //追跡キャラが消えた時の処理
    void DeleteTargetPointer(BoxCollider* target);

    void Update(float delta_time);
    void Draw() const;
};