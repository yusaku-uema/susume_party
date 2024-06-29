#pragma once
#include <vector>
#include"define.h"

#define ENEMY_NUM 5

class EnemyManager
{
private:

    enum ENEMY_TYPE
    {
        SLIME,//�X���C��
        FLOWER,//�t�����[
        BIRD,//��
        FAIRY,//�d��
        BLACKMAGE, //�{�X

        END
    };

    class Stage* stage;
    class PlayerManager* player_manager;
    class AttackManager* attack_manager;

    std::vector<class EnemyBase*>enemy;

    int enemy_image[ENEMY_TYPE::END][4][5];

    bool dead_boss;

    void SpawnEnemy(ENEMY_TYPE enemy_type, DATA location);
    void SetEnemy();

public:

    EnemyManager(); //�Ăяo�������G�ƍ��W��
    ~EnemyManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);

    void Update(float delta_time);
    void Draw() const;
    
    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//�U���������������m���߂�
    bool NextTransition();

    class BoxCollider* GetEnemyData(int enemy_num)const;
    int GetEnemyNum()const;
};