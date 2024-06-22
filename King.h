#pragma once
#include"NpcBase.h"

class King : public NpcBase
{
public:
    King();
    ~King();

    void Update()override;
    void Draw()const override;
};