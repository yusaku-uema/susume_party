#pragma once
#include "CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

class Bird :
    public CharacterBase
{
private:

    float distance_moved; //����������

    bool start_attack; //�U���J�n
    bool move_up; //��Ɉړ�
    bool move_left; //���ɓ���

public:

    Bird(); //�R���X�g���N�^
    ~Bird(); //�f�X�g���N�^

    void Update(float delta_time, class Stage* stage, class PlayerManager* player); //�X�V����
    void Draw(float camera_work) const; //�`��֌W

    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�

};

