#pragma once
#include"PlayerBase.h"


#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    class Stage* stage;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    class PlayerBase* player[4];
    
    int dead_player_count;
    int arrow_image;//�擪�v���C���[���w�����摜
    float draw_arrow_time;//���̕\������

    void DeadPlayerSorting(int dead_player_index);//���S�L�����̕��ёւ�
    void PlayerSorting();//�v���C���[���ёւ�

public:

    PlayerManager(class Ui* ui);
    ~PlayerManager();

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//�U���������������m���߂�

    bool Update(float delta_time);//�߂�l�i�v���C���[���S�ł�����@TRUE��Ԃ��j
    void Draw() const;

    PlayerBase* GetPlayerData()const;

    void SetPointer(class Stage* stage, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
    
};