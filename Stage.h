#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"Slime.h"
#include"PlayerBase.h"

class Stage
{
private:
    class PlayerBase* player[3];
    class Slime* slime;
    std::vector<Block>block;
    int block_image[2];//�u���b�N�摜
    int sky_image;//��摜
    float fps;

    void SetStage();//�X�e�[�W�𐶐�
public:
    Stage();
    ~Stage();

    void Initialize();//������
    void Update(float delta_time);
    void Draw() const;
    bool HitBlock(BoxCollider* bc)const;
};