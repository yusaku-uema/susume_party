#pragma once
#include"NpcBase.h"

class King : public NpcBase
{
public:
    King(DATA location, DATA size, class Stage* stage, class PlayerManager* player_manager, const char* text_data_name);
    ~King();

    void Update()override;
    void Draw()const override;
};