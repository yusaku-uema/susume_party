#pragma once
#include <vector>
#include"define.h"

#define ENEMY_NUM 5

class EnemyManager
{
private:

    enum ENEMY_TYPE
    {
        SLIME,//スライム
        FLOWER,//フラワー
        BIRD,//鳥
        FAIRY,//妖精
        BLACKMAGE, //ボス

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

    EnemyManager(); //呼び出したい敵と座標を
    ~EnemyManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);

    void Update(float delta_time);
    void Draw() const;
    
    bool CheckHitDamage(class BoxCollider* bc, int attack_power);//攻撃が当たったか確かめる
    bool NextTransition();

    class BoxCollider* GetEnemyData(int enemy_num)const;
    int GetEnemyNum()const;
};