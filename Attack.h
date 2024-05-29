#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    class Stage* stage;
    
    int attack_image;//�U���摜
    int attack_power;//�U����
    DATA speed;//�X�s�[�h
    float duration_time;//�U���p������

    int* image;
    int image_num;
    int explosion_image[8];
    int draw_image_num;
    float change_image_time;

public:
    Attack(class Stage* stage, DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);
    ~Attack();

    bool Update(float delta_time, class PlayerManager* player_manager, EnemyManager* enemy_manager);
    void Draw()const;

    int GetAttackPower()const;
};