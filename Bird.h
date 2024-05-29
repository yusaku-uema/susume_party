#pragma once
#include"PlayerManager.h"
#include"EnemyManager.h"
#include"EnemyBase.h"
#include"Stage.h"



enum class BIRD_STATE
{
    NORMAL,   //�ʏ�ړ� 
    ATTACK, //�U��
    STANDBY, //�ҋ@�B
    RETURN //�U����A�U������O�̍��W�ɖ߂�
};



class Bird :
    public EnemyBase
{
private:

    int time;//�U���ҋ@����
    int bird_image[11]; //�o�[�h�̉摜
    int image_type; //�g���摜�̗v�f�w��
    long int animation_time; //�摜�ؑւɎg���ϐ�
  
   

    float distance_moved; //����������
    float attack_speed; //�U�����x
    float distance; //����Ƃ̋���
    float dx, dy; //�ω���

    bool move_up; //��Ɉړ�
    bool move_left; //���ɓ���
    bool direction; //�����Ă������
    bool lock_on; //�v���C���[�ɑ_�����߂�B


    BIRD_STATE state; //�o�[�h�̏��
    DATA old_location; //�O�̍��W
    DATA player_location; //�U�����̃v���C���[�̈ʒu
    

public:

    Bird(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //�R���X�g���N�^
    ~Bird(); //�f�X�g���N�^

    void Update()override; //�X�V����
    void Draw() const override; //�`��֌W
    void Move(); //�ʏ�ړ�
    void Standby(); //�U����������
    void Attack(); //�U��
    void Retur(); //�U���㌳�̍��W�ɖ߂�B

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

