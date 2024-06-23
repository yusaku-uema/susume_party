#pragma once
#include"Attack.h"
#include"Stage.h"

#define ATTACK_TYPE_NUM 7//�U����ށi�A�j���[�V�����̎�ށj

////�U���̎��
enum ATTACK_TYPE
{
    NONE,
    BIG_EXPLOSION,//�唚��
    EXPLOSION,//����
    SMALL_EXPLOSION,//������
    SLASHING,//�a��
    SPIN_SLASH,//��]�a��
    FIRE_BALL
};

class AttackManager
{
private:
    std::vector<class Attack>player_attack;
    std::vector<class Attack>enemy_attack;

    class Stage* stage;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;

    int attack_image[ATTACK_TYPE_NUM][10];//�U���摜
    const int attack_image_num[ATTACK_TYPE_NUM] = { 0, 8, 5, 4, 5, 2, 1 };//�U���摜�̐�
   
public:
    AttackManager();
    ~AttackManager();

    void Initialize(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);

    //�G�̍U����ǉ�(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddEnemyAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size);
    //�v���C���[�̍U����ǉ�(�U�����W�A�U���T�C�Y�A�U���X�s�[�h�A�U���̌p�����ԁA�U���́A�U���̉摜)
    void AddPlayerAttack(DATA location, DATA size, DATA speed, class BoxCollider* bc, bool delete_hit_stage, bool delete_hit_chara, float duration_time, int attack_power, ATTACK_TYPE attack_type, float image_size);

    //�ǐՃL���������������̏���
    void DeleteTargetPointer(BoxCollider* target);

    void Update(float delta_time);
    void Draw() const;
};