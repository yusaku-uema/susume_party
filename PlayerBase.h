#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 60//�ߋ����񕪂̃W�����v�̋L�^

class PlayerBase : public CharacterBase
{
private:
    void MoveX(class Stage* stage, CharacterBase* character);//X���W�̍X�V
    void MoveY(class Stage* stage, CharacterBase* character);//Y���W�̍X�V
    bool jump_log[JUMP_LOG];//�ߋ����񕪂̃W�����v�̋L�^
public:
    PlayerBase();
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, CharacterBase* character);
    void Draw() const;
};