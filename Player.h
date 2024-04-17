#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class Player : public CharacterBase
{
private:
    bool is_walking = false;//�����Ă��邩�H
    bool is_jump = false;//�W�����v���Ă��邩�H
    bool is_facing_left = false;//���������Ă��邩�H
public:
    Player();
    ~Player();

    void Update(float delta_time, class Stage* stage);
    void Draw() const;
};