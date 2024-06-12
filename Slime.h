#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class SLIME_STATE
{
    NORMAL,   //�ʏ�ړ� 
    STANDBY, //�ҋ@�B
    ATTACK, //�U��
    DEATH //���S
};

class Slime : public EnemyBase
{
private:
    
    int slime_image[12]; //�X���C���̉摜
    int image_type; //�g���摜�̎w��

    long int time;//���ԑ���

    bool move_left; //���ɓ�����

    SLIME_STATE state; //�X���C���̏��

public:
    Slime(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location);
    ~Slime();

    void Update()override;
    void Draw() const override;
    void Move(); //�ʏ�ړ�
    void Attack(); //�U��
    void Standby(); //�ҋ@

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�


};