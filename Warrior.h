#pragma once
#include"PlayerBase.h"

class Warrior : public PlayerBase
{
private:

public:
    Warrior(class Stage* stage, class PlayerManager* player_manager);
    ~Warrior();
};