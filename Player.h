#pragma once
#include"Stage.h"

class Player : public BoxCollider
{
private:
    int player_image;//�v���C���[�摜

    DATA speed;
    bool is_walking = false;//�����Ă��邩�H
    bool is_jump = false;//�W�����v���Ă��邩�H
    bool is_facing_left = false;//���������Ă��邩�H
public:
    Player();
    ~Player();

    void Update(float delta_time, class Stage* stage);
    void Draw() const;
};