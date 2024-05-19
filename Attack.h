#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    int attack_image;//UŒ‚‰æ‘œ
    int attack_power;//UŒ‚—Í
    DATA speed;//ƒXƒs[ƒh
    float duration_time;//UŒ‚Œp‘±ŠÔ
public:
    Attack(DATA location, DATA size,DATA speed, float duration_time,int attack_power, int attack_image);
    ~Attack();

    bool Update(float delta_time, class Stage* stage);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
};