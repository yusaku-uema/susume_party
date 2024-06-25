#pragma once
#include"BoxCollider.h"

class Block : public BoxCollider
{
private:
    int block_image;//ƒuƒƒbƒN‰æ‘œ
    
public:

    Block(DATA location, int block_image);
    ~Block();

    bool Draw(float camera_work)const;
};