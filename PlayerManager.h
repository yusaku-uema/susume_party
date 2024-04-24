#pragma once
#include"PlayerBase.h"
#include"Attack.h"
#include"Stage.h"

#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    std::vector<Attack>attack;
    class PlayerBase* player[4];
    void PlayerSorting();//�v���C���[���ёւ�
public:

    PlayerManager();
    ~PlayerManager();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;

    void AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    DATA GetPlayerLocation()const;
};