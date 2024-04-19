#pragma once
#include"CharacterBase.h"
#include"Stage.h"

#define JUMP_LOG 60//過去数回分のジャンプの記録

class PlayerBase : public CharacterBase
{
private:
    void MoveX(class Stage* stage, CharacterBase* character);//X座標の更新
    void MoveY(class Stage* stage, CharacterBase* character);//Y座標の更新
    bool jump_log[JUMP_LOG];//過去数回分のジャンプの記録
public:
    PlayerBase();
    ~PlayerBase();

    void Update(float delta_time, class Stage* stage, CharacterBase* character);
    void Draw() const;
};