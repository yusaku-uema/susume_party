#pragma once
#include"define.h"

#define KEY_NUM 11

enum class KEY_TYPE
{
	A,
	B,
	X,
	Y,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	L,
	R,
	START
};

struct KEY
{
	bool now_flg;
	bool old_flg;
};

struct STICK_ANGLE
{
	int x, y;
};

class Key //�L�[�̍X�V����
{
private:

	static KEY key[KEY_NUM];

	static STICK_ANGLE l_stick_angle;
	static STICK_ANGLE r_stick_angle;

public:

	static void Initialization(); //������
	static void Update();
	static bool KeyPressed(KEY_TYPE key_type);//�����Ă�Ƃ�
	static bool KeyUp(KEY_TYPE key_type);//�������Ƃ�
	static bool KeyDown(KEY_TYPE key_type);//�������u��

	static DATA GetStickAngle(KEY_TYPE key);
};