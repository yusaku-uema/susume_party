#pragma once
#include"BoxCollider.h"
#include"Stage.h"

class Attack : public BoxCollider
{
private:
    BoxCollider* target;//�ǐՑ���

    int* attack_image;//�U���摜
    int image_num;//�摜�̐�

    float image_change_time;//�摜�؂�ւ�����
    int draw_image_num;//�\�����̉摜
    float image_size;//�摜�T�C�Y�i�摜�{���j

    int attack_power;//�U����
    DATA speed;//�X�s�[�h
    float duration_time;//�U���p������
    int angle;//�摜�̊p�x

    bool delete_hit_stage;//�X�e�[�W�ɓ����������ɏ������H
    bool delete_hit_chara;//�L�����N�^�[�ɓ����������ɏ������H

    void TrackingCharacter(); //�ǔ�

public:
    Attack(DATA location, DATA size, DATA speed, BoxCollider* target,bool delete_hit_stage, bool delete_hit_chara,
        float duration_time, int attack_power, int* attack_image, int image_num, float image_size);
    ~Attack();

    bool Update(float delta_time, class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager);
    void Draw(float camera_work)const;

    int GetAttackPower()const;
    int GetImageSize()const;

    void DeleteTargetPointer(BoxCollider* target);//�ǐՒ��̃L�����̃|�C���^�[�̏���
};