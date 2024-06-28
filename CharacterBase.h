#pragma once
#include"BoxCollider.h"
#include"EnemyManager.h"

class CharacterBase : public BoxCollider
{
protected:
    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

    DATA speed;//スピード
    bool is_facing_left; //左を向いているか？
    float image_change_time;//画像切り替え時間
    int draw_image_num;//表示画像の番号
    
    float CalculateDistance(class BoxCollider* character)const;

public:
    CharacterBase(DATA location, DATA size);
    ~CharacterBase();

    void SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
};