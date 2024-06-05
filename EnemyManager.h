#pragma once
#include <vector>

#define ENEMY_NUM 5

class EnemyManager
{
private:
    class Stage* stage;
    class PlayerManager* player_manager;
    class AttackManager* attack_manager;

    std::vector<class EnemyBase*>enemy;

public:

    EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~EnemyManager();

    void Update(float delta_time);
    void Draw() const;

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//UŒ‚‚ª“–‚½‚Á‚½‚©Šm‚©‚ß‚é
};