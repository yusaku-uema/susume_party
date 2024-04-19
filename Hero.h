#pragma once
#include"PlayerBase.h"
#include"Stage.h"

class PlayerBase : public CharacterBase
{
public:
    PlayerBase();
    ~PlayerBase();

    virtual void Update(float delta_time, class Stage* stage, CharacterBase* character) = 0;
    virtual void Draw() const = 0;
};