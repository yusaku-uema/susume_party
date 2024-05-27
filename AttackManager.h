#pragma once
#include"Attack.h"
#include"Stage.h"

class AttackManager
{
private:
    std::vector<class Attack>player_attack;
    std::vector<class Attack>enemy_attack;

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
   
public:

    AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    ~AttackManager();

    //敵の攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);
    //プレイヤーの攻撃を追加(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    void Update(float delta_time);
    void Draw() const;
};