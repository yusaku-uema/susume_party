#pragma once
#include"Attack.h"
#include"Stage.h"

class AttackManager
{
private:
    std::vector<Attack>attack;

public:

    AttackManager();
    ~AttackManager();

    //�U�����鏈��(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;
};