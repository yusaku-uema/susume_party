#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class Player : public CharacterBase
{
private:
    bool is_walking = false;//歩いているか？
    bool is_jump = false;//ジャンプしているか？
    bool is_facing_left = false;//左を向いているか？
public:
    Player();
    ~Player();

    void Update(float delta_time, class Stage* stage);
    void Draw() const;
};