#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"Player.h"

class Stage
{
private:
    class Player* player;
    std::vector<Block>block;

    void SetStage();//�X�e�[�W�𐶐�
public:
    Stage();
    ~Stage();

    void Initialize();//������
    void Update(float delta_time);
    void Draw() const;
    bool HitBlock(BoxCollider* bc)const;
};