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

class Key //キーの更新処理
{
private:

	static KEY key[KEY_NUM];

	static STICK_ANGLE l_stick_angle;
	static STICK_ANGLE r_stick_angle;

public:

	static void Initialization(); //初期化
	static void Update();
	static bool KeyPressed(KEY_TYPE key_type);//押してるとき
	static bool KeyUp(KEY_TYPE key_type);//離したとき
	static bool KeyDown(KEY_TYPE key_type);//押した瞬間

	static DATA GetStickAngle(KEY_TYPE key);
};