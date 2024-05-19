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

    //攻撃する処理(攻撃座標、攻撃サイズ、攻撃スピード、攻撃の継続時間、攻撃力、攻撃の画像)
    void AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    void Update(float delta_time);
    void Draw() const;
};