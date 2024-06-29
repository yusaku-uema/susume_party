#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

class Flower : public EnemyBase
{
public:

    Flower(DATA location, int enemy_image[ENEMY_STATE::END][5], class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~Flower();

    void Update(float delta_time)override; //XVˆ—
    void Draw(DATA draw_location) const override; //•`‰æŠÖŒW
};

