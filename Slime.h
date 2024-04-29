#pragma once
#include"CharacterBase.h"
#include"PlayerManager.h"
#include"Stage.h"

enum class SLIME_STATE
{
    NORMAL,   //�ʏ�ړ� 
    ATTACK //�U��
};

class Slime : public CharacterBase
{
private:
    
    int slime_image[12]; //�X���C���̉摜
    int image_type; //�g���摜�̎w��

    long int time;//���ԑ���

    bool move_left; //���ɓ�����

    SLIME_STATE state; //�X���C���̏��

public:
    Slime();
    ~Slime();

    void Update(float delta_time, class Stage* stage, class PlayerManager* player);
    void Draw(float camera_work) const;
    void Move(class Stage* stage, class PlayerManager* player); //�ʏ�ړ�
    void Attack(class Stage* stage, class PlayerManager* player, float delta_time); //�U��

    float CalculateDistance(class PlayerManager* player); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�


};