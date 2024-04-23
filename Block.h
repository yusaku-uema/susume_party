#pragma once
#include"BoxCollider.h"

class Block : public BoxCollider
{
private:
    BLOCK_TYPE type;//�u���b�N�̎��
    int block_image;//�u���b�N�摜
    
public:

    Block(DATA location, BLOCK_TYPE type, int block_image);
    ~Block();

    void Draw(float camera_work)const;
    BLOCK_TYPE GetType()const;
};