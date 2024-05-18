#pragma once
#include"PlayerBase.h"
#include"Stage.h"

#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    class PlayerBase* player[4];

    int arrow_image;//�擪�v���C���[���w�����摜
    float draw_arrow_time;//���̕\������

    int alive_player;//�����Ă�v���C���[��

    void DeadPlayerSorting();//���S�L�����̕��ёւ�
    void PlayerSorting();//�v���C���[���ёւ�
public:

    PlayerManager(class Stage* stage, class Ui* ui);
    ~PlayerManager();

    void Update(float delta_time);
    void Draw(float camera_work) const;

    DATA GetPlayerLocation()const;
    
};