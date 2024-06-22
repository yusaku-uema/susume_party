#pragma once
#include"CharacterBase.h"

class NpcBase : public CharacterBase
{
protected:
    int npc_image[4];

public:
    NpcBase(DATA location, DATA size);
    ~NpcBase();

    virtual void Update() {};
    virtual void Draw()const {};
};