#pragma once
#include"Attack.h"
#include"Stage.h"

class AttackManager
{
private:
    std::vector<class Attack>player_attack;
    std::vector<class Attack>enemy_attack;

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
   
public:

    AttackManager(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    ~AttackManager();

    //�G�̍U����ǉ�(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);
    //�v���C���[�̍U����ǉ�(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddPlayerAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image);

    void Update(float delta_time);
    void Draw() const;
};