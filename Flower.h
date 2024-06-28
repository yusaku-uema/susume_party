#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

class Flower : public EnemyBase
{
    int flower_image[7]; //�t�����[�̉摜
public:

    Flower(DATA location, class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~Flower();

    void Update(float delta_time)override; //�X�V����
    void Draw(DATA draw_location) const override; //�`��֌W
};

