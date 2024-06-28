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

    DATA speed;//�X�s�[�h
    bool is_facing_left; //���������Ă��邩�H
    float image_change_time;//�摜�؂�ւ�����
    int draw_image_num;//�\���摜�̔ԍ�
    
    float CalculateDistance(class BoxCollider* character)const;

public:
    CharacterBase(DATA location, DATA size);
    ~CharacterBase();

    void SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager);
};