#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    int* attack_image;//UŒ‚‰æ‘œ
    int image_num;//‰æ‘œ‚Ì”
    float image_change_time;//‰æ‘œØ‚è‘Ö‚¦ŠÔ
    int draw_image_num;//•\¦’†‚Ì‰æ‘œ

    int attack_power;//UŒ‚—Í
    DATA speed;//ƒXƒs[ƒh
    float duration_time;//UŒ‚Œp‘±ŠÔ

public:
    Attack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int* attack_image, int image_num);
    ~Attack();

    bool Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, EnemyManager* enemy_manager);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
};