#pragma once
#include"PlayerBase.h"

class Wizard : public PlayerBase
{
private:
    void SpecialSkill()override;
public:
    Wizard();
    ~Wizard();
};