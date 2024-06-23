#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class NpcBase : public CharacterBase
{
private:
    char text_data_name[256];

protected:
    int npc_image[4];

public:
    NpcBase(DATA location, DATA size, const char* text_data_name);
    ~NpcBase();

    virtual void Update() = 0;
    virtual void Draw()const = 0;

    const char* GetTextDataName()const;
};