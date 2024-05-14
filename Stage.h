#pragma once
#include <vector>
#include"define.h"
#include"Block.h"
#include"Slime.h"
#include"Bird.h"
#include"Flower.h"
#include"PlayerManager.h"
#include"AttackManager.h"

class Stage
{
private:
    class PlayerManager* player_manager;
    class AttackManager* attack_manager;
    class Slime* slime;
    class Bird* bird;
    class Flower* flower;
    std::vector<Block>block;

    int block_image[2];//�u���b�N�摜
    int sky_image;//��摜

    float fps;
    float camera_work;

    void SetStage();//�X�e�[�W�𐶐�

public:
    Stage();
    ~Stage();

    void Initialize();//������
    void Update(float delta_time);
    void Draw() const;

    void SetCameraWork();
    bool HitBlock(BoxCollider* bc)const;
    void AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);
};