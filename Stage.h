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

    int block_image[BLOCK_TYPE_NUM];//�u���b�N�摜
    int back_ground_image[4];//�w�i�摜

    float camera_work;
    float center_location_x;
    float stop_time;//�������~�߂鎞��
    float time_count;//���Ԃ̃J�E���g

    void SetStage();//�X�e�[�W�𐶐�

public:
    Stage(class Ui* ui);
    ~Stage();

    bool Update(float delta_time);//�߂�l�i�v���C���[���S�ł�����@TRUE��Ԃ��j
    void Draw() const;

    bool HitBlock(class BoxCollider* bc)const;

    void SetStopTime(float stop_time);

    void SetCameraWork();
    float GetCameraWork()const;
    float GetCenterLocationX()const;
};