#pragma once
#include"PlayerBase.h"
#include"Stage.h"

#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    class PlayerBase* player[4];
    void PlayerSorting();//�v���C���[���ёւ�
public:

    PlayerManager();
    ~PlayerManager();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;

    DATA GetPlayerLocation()const;
};