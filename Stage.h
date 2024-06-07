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
    int back_ground_image[4];//背景画像

    float camera_work;
    float center_location_x;
    float stop_time;//処理を止める時間
    float time_count;//時間のカウント

    void SetStage();//ステージを生成

public:
    Stage(class Ui* ui);
    ~Stage();

    bool Update(float delta_time);//戻り値（プレイヤーが全滅したら　TRUEを返す）
    void Draw() const;

    bool HitBlock(class BoxCollider* bc)const;

    void SetStopTime(float stop_time);

    void SetCameraWork();
    float GetCameraWork()const;
    float GetCenterLocationX()const;
};