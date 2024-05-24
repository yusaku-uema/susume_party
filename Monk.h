#pragma once
#include"PlayerBase.h"

class Monk : public PlayerBase
{
private:

public:
    Monk(class Stage* stage, class PlayerManager* player_manager);
    ~Monk();
};