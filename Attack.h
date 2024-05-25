#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;

    int attack_image;//�U���摜
    int attack_power;//�U����
    DATA speed;//�X�s�[�h
    float duration_time;//�U���p������
public:
    Attack(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, 
        DATA location, DATA size,DATA speed, float duration_time,int attack_power, int attack_image);
    ~Attack();

    bool Update(float delta_time, bool is_player_attack);
    void Draw()const;

    int GetAttackPower()const;
};