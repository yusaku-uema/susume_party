#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"Slime.h"
#include"Player.h"

class Stage
{
private:
    class Player* player;
    class Slime* slime;
    std::vector<Block>block;
    int block_image[2];//ブロック画像
    int sky_image;//空画像

    void SetStage();//ステージを生成
public:
    Stage();
    ~Stage();

    void Initialize();//初期化
    void Update(float delta_time);
    void Draw() const;
    bool HitBlock(BoxCollider* bc)const;
};