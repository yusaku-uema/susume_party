#pragma once
#include"Attack.h"
#include"Stage.h"

class AttackManager
{
private:
    std::vector<class Attack>attack;
    class Stage* stage;
   
public:

    AttackManager(class Stage* stage);
    ~AttackManager();

    //�U�����鏈��(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    void Update(float delta_time);
    void Draw() const;
};