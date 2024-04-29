#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class Slime : public CharacterBase
{
private:
    
    int slime_image[12]; //スライムの画像
    int image_type; //使う画像の指定

    long int time;//時間測定

    bool move_left; //左に動くか

public:
    Slime();
    ~Slime();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;
};