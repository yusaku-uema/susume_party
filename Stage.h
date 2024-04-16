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

    void SetStage();//ステージを生成
public:
    Stage();
    ~Stage();

    void Initialize();//初期化
    void Update(float delta_time);
    void Draw() const;
    bool HitBlock(BoxCollider* bc)const;
};