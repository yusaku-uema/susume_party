#pragma once
#include <vector>
#include"define.h"

#define ENEMY_NUM 5

typedef enum ENEMY_TYPE
{
    SLIME=0,
    FLOWER,
    BIRD,
    FAIRY,

    BLACKMAGE //�{�X
};


class EnemyManager
{
private:
    class Stage* stage;
    class PlayerManager* player_manager;
    class AttackManager* attack_manager;

    std::vector<class EnemyBase*>enemy;

public:

    EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //�Ăяo�������G�ƍ��W��
    ~EnemyManager();

    void Update(float delta_time);
    void Draw() const;
    void SpawnEnemy(int enemy_type,DATA location);
    void SetEnemy();

    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//�U���������������m���߂�
    
    class BoxCollider* GetEnemyData(int enemy_num)const;
    int GetEnemyNum()const;
};