#pragma once
#include"PlayerBase.h"

class Hero : public PlayerBase
{
private:
    void SpecialSkill()override;
public:
    Hero();
    ~Hero();
};