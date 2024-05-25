#pragma once
#include"PlayerBase.h"

class Wizard : public PlayerBase
{
private:

public:
    Wizard(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~Wizard();
};