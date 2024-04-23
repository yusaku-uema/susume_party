#pragma once
#include"CharacterBase.h"
#include"Stage.h"

class Slime : public CharacterBase
{
private:
    
public:
    Slime();
    ~Slime();

    void Update(float delta_time, class Stage* stage);
    void Draw(float camera_work) const;
};