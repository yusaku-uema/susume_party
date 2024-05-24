#pragma once
#include"PlayerBase.h"

class Hero : public PlayerBase
{
private:

public:
    Hero(class Stage* stage, class PlayerManager* player_manager);
    ~Hero();
};