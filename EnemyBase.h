#pragma once
#include"PlayerManager.h"

class EnemyBase : public CharacterBase
{
protected:

	int time; //����
	int image_type; //�g���摜�̗v�f�w��
	int death_effects[4]; //���S�G�t�F�N�g
	long int animation_time; //�摜�ؑւɎg���ϐ�

	float distance_moved; //����������
	float attack_speed; //�U�����x
	float distance; //����Ƃ̋���
	float dx, dy; //�ω���

	bool direction; //�����Ă������
	bool death_animation; //���S�A�j���[�V�����J�n

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw()const = 0;

	bool HitDamege(BoxCollider* bc, int attack_power)override;

};

