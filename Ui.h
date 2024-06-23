#pragma once
#include "PlayerBase.h"

struct DRAW_PLAYER_STATE
{
    int hp;
    int mp;
    int image_type;
};

class Ui
{
private:
    class PlayerBase** player;
    DRAW_PLAYER_STATE draw_player_state[4];
    int player_image[3][4];

public:
    Ui(PlayerBase** player_base);
    ~Ui();

    void Update();
    void Draw() const;
};