#pragma once
#include"EnemyBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class FLOWER_STATE
{
    ATTACK, //�U��
    STANDBY, //�ҋ@
    BREAKTIME, //�U����̑ҋ@����
    DEATH //�G�l�~�[���S
};

class Flower :
    public EnemyBase
{
    int time; //�A�j���[�V�������ԑ���
    int flower_image[7]; //�t�����[�̉摜
    int image_type; //�g���摜�̗v�f�w��
    int standby_time; //�U����̑ҋ@���ԑ���
    long int animation_time; //�摜�ؑւɎg���ϐ�


    bool start_attack; //�U���J�n
    bool direction; //�����Ă������

    FLOWER_STATE state; //�t�����[�̏��


public:

    Flower(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager, DATA location);
    ~Flower();

    void Update()override; //�X�V����
    void Draw() const override; //�`��֌W
    void Attack(); //�U��

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

