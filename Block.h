#pragma once
#include"BoxCollider.h"

class Block : public BoxCollider
{
private:
    BLOCK_TYPE type;//ブロックの種類
    int block_image;//ブロック画像
    
public:

    Block(DATA location, BLOCK_TYPE type, int block_image);
    ~Block();

    void Draw(float camera_work)const;
    BLOCK_TYPE GetType()const;
};