#pragma once
#include"PlayerBase.h"


#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    class PlayerBase* player[4];
    class Stage* stage;

    int arrow_image;//�擪�v���C���[���w�����摜
    float draw_arrow_time;//���̕\������

    void DeadPlayerSorting(int dead_player);//���S�L�����̕��ёւ�
    void PlayerSorting();//�v���C���[���ёւ�
public:

    PlayerManager(class Stage* stage, class AttackManager* attack_manager, class Ui* ui);
    ~PlayerManager();

    void CheckHitDamage(BoxCollider* bc, int attack_power);//�U���������������m���߂�

    void Update(float delta_time);
    void Draw() const;

    DATA GetPlayerLocation()const;
    
};