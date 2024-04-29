#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class Slime : public CharacterBase
{
private:
    
    int slime_image[12]; //�X���C���̉摜
    int image_type; //�g���摜�̎w��

    long int time;//���ԑ���

    bool move_left; //���ɓ�����

public:
    Slime();
    ~Slime();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;
};