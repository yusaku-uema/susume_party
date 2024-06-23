#pragma once
#include"PlayerBase.h"
#include"Message.h"

#define PLAYER_NUM 4//�v���C���[�i�L�����̐��j

class PlayerManager
{
private:
    class Stage* stage;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class Message* message;
    class Ui* ui;

    class PlayerBase* player[4];
    
    int arrow_image;//�擪�v���C���[���w�����摜
    float draw_arrow_time;//���̕\������

    void DeadPlayerSorting(int dead_player_index);//���S�L�����̕��ёւ�
    void PlayerSorting();//�v���C���[���ёւ�

public:

    PlayerManager();
    ~PlayerManager();

    void Initialize(class Stage* stage, class EnemyManager* enemy_manager, class AttackManager* attack_manager);

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//�U���������������m���߂�

    bool Update(float delta_time);//�߂�l�i�v���C���[���S�ł�����@TRUE��Ԃ��j
    void Draw() const;

    PlayerBase* GetPlayerData()const;

    void SetMessage(const char* text_data_name);//���b�Z�[�W���Z�b�g
    bool GetiIsTalking()const;//��b�����m���߂�֐�
    void SetPartyState(bool party_state);//�p�[�e�B�[��؂藣�����ǂ���
    void AddPlayerHp(int add_hp);//�p�[�e�B�[�S�̂�HP���Z
};