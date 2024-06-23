#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"PlayerManager.h"
#include"EnemyManager.h"
#include"AttackManager.h"
#include"NpcManager.h"

struct BACK_GROUND_BLOCK
{
    DATA location;
    int type;
};

class Stage
{
private:
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class NpcManager* npc_manager;
    
    std::vector<class Block>block;
    std::vector<BACK_GROUND_BLOCK>back_ground_block;

    int block_image[BLOCK_TYPE_NUM];//ブロック画像
    int back_ground_image[4];//背景画像

    float camera_work;
    float center_location_x;
    bool next_transition;

    void SetStage();//ステージを生成

public:
    Stage();
    ~Stage();

    bool Update(float delta_time);//戻り値（プレイヤーが全滅したら　TRUEを返す）
    void Draw() const;

    bool HitBlock(class BoxCollider* bc)const;
    bool NextTransition();

    void SetCameraWork();
    float GetCameraWork()const;
    float GetCenterLocationX()const;
};