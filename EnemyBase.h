#pragma once
#include"PlayerManager.h"
#include"Stage.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //����
	int image_type; //�g���摜�̗v�f�w��
	long int animation_time; //�摜�ؑւɎg���ϐ�

	float distance_moved; //����������
	float attack_speed; //�U�����x
	float distance; //����Ƃ̋���
	float dx, dy; //�ω���

	bool direction; //�����Ă������
	bool dead_boss;

	DATA spawn_location; //�X�|�[���������W���o����

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw()const = 0;

	virtual void DrawHPBar(const int) const;

	bool ScopeoOfActivity(float camera_work); //�����͈͊O�ɏo�Ă��Ȃ��̂�

	bool HitDamege(BoxCollider* bc, int attack_power)override;
	bool GetDeadBoss();

};

