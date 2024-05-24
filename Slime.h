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
    Slime(class Stage* stage, class PlayerManager* player_manager);
    ~Slime();

    void Update(float delta_time);
    void Draw() const;
    void Move(); //�ʏ�ړ�
    void Attack(float delta_time); //�U��

    float CalculateDistance(); //�Ƃ肠�����擪�v���C���[�̋����v�Z�������B�A�ł����4�l�܂Ƃ߂�


};