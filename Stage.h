#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"Slime.h"
#include"Bird.h"
#include"PlayerManager.h"

class Stage
{
private:
    class PlayerManager* player_manager;
    class Slime* slime;
    class Bird* bird;
    std::vector<Block>block;

    int block_image[2];//ブロック画像
    int sky_image;//空画像

    float fps;
    float camera_work;


    void SetStage();//ステージを生成
public:
    Stage();
    ~Stage();

    void Initialize();//初期化
    void Update(float delta_time);
    void Draw() const;

    void SetCameraWork();
    bool HitBlock(BoxCollider* bc)const;
};