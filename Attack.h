#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    int* attack_image;//�U���摜
    int image_num;//�摜�̐�
    float image_change_time;//�摜�؂�ւ�����
    int draw_image_num;//�\�����̉摜

    int attack_power;//�U����
    DATA speed;//�X�s�[�h
    float duration_time;//�U���p������

public:
    Attack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int* attack_image, int image_num);
    ~Attack();

    bool Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, EnemyManager* enemy_manager);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
};