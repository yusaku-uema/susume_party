#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    int attack_image;//�U���摜
    int attack_power;//�U����
    DATA speed;//�X�s�[�h
    float duration_time;//�U���p������
public:
    Attack(DATA location, DATA size,DATA speed, float duration_time,int attack_power, int attack_image);
    ~Attack();

    bool Update(float delta_time, class Stage* stage);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
};