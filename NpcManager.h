#pragma once
#include <vector>
#include"NpcBase.h"

class NpcManager
{
private:

    class Stage* stage;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    std::vector<class NpcBase*>npc;

public:

    NpcManager();
    ~NpcManager();

    void Update(float delta_time);
    void Draw() const;

    void SetPointer(class Stage* stage, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
};