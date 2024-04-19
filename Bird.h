#pragma once
#include "CharacterBase.h"
#include"Stage.h"

class Bird :
    public CharacterBase
{
private:

    float distance_moved; //����������

    bool move_up; //��Ɉړ�
    bool move_left; //���ɓ���

public:

    Bird(); //�R���X�g���N�^
    ~Bird(); //�f�X�g���N�^

    void Update(float delta_time, class Stage* stage); //�X�V����
    void Draw() const; //�`��֌W
};

