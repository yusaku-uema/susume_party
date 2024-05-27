#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"PlayerManager.h"
#include"EnemyManager.h"
#include"AttackManager.h"

class Stage
{
private:
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    
    std::vector<class Block>block;

    int block_image[BLOCK_TYPE_NUM];//ブロック画像
    int sky_image;//空画像

    float camera_work;
    float center_location_x;

    void SetStage();//ステージを生成

public:
    Stage(class Ui* ui);
    ~Stage();

    void Update(float delta_time);
    void Draw() const;

    bool HitBlock(class BoxCollider* bc)const;

    void SetCameraWork();
    float GetCameraWork()const;
    float GetCenterLocationX()const;
};