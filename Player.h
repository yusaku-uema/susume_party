#pragma once
#include"Stage.h"

class Player : public BoxCollider
{
private:
    int player_image;//プレイヤー画像

    DATA speed;
    bool is_walking = false;//歩いているか？
    bool is_jump = false;//ジャンプしているか？
    bool is_facing_left = false;//左を向いているか？
public:
    Player();
    ~Player();

    void Update(float delta_time, class Stage* stage);
    void Draw() const;
};