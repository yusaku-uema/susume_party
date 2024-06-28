#include"DxLib.h"
#include "Key.h"

KEY Key::key[KEY_NUM];//static変数はここでも定義しないといけない
STICK_ANGLE Key::l_stick_angle;
STICK_ANGLE Key::r_stick_angle;

void Key::Initialization()
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		key[i] = { FALSE , FALSE};
	}

	l_stick_angle = { 0,0 };
	l_stick_angle = { 0,0 };
}

void Key::Update()
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		key[i].old_flg = key[i].now_flg;
		key[i].now_flg = FALSE;
	}

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))key[static_cast<int>(KEY_TYPE::A)].now_flg = TRUE;//Aボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)) key[static_cast<int>(KEY_TYPE::B)].now_flg = TRUE;//Bボタンが押されているか
	//if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6))key[static_cast<int>(KEY_TYPE::X)].now_flg = TRUE;//Aボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4)) key[static_cast<int>(KEY_TYPE::Y)].now_flg = TRUE;//Bボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)) key[static_cast<int>(KEY_TYPE::R)].now_flg = TRUE;//Rボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)) key[static_cast<int>(KEY_TYPE::L)].now_flg = TRUE;//Lボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP))key[static_cast<int>(KEY_TYPE::UP)].now_flg = TRUE;//UPボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))key[static_cast<int>(KEY_TYPE::DOWN)].now_flg = TRUE;//DOWNボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT))key[static_cast<int>(KEY_TYPE::RIGHT)].now_flg = TRUE;//RIGHTボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT))key[static_cast<int>(KEY_TYPE::LEFT)].now_flg = TRUE;//LEFTボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8)) key[static_cast<int>(KEY_TYPE::START)].now_flg = TRUE;//スタートボタンが押されているか

	if (CheckHitKey(KEY_INPUT_D))key[static_cast<int>(KEY_TYPE::RIGHT)].now_flg = TRUE;//RIGHTボタンが押されているか
	if (CheckHitKey(KEY_INPUT_A))key[static_cast<int>(KEY_TYPE::LEFT)].now_flg = TRUE;//LEFTボタンが押されているか
	if (CheckHitKey(KEY_INPUT_SPACE))key[static_cast<int>(KEY_TYPE::A)].now_flg = TRUE;//Aボタンが押されているか
	if (CheckHitKey(KEY_INPUT_LSHIFT))key[static_cast<int>(KEY_TYPE::B)].now_flg = TRUE;//Aボタンが押されているか



	GetJoypadAnalogInputRight(&r_stick_angle.x, &r_stick_angle.y, DX_INPUT_PAD1); // 入力状態を取得

	GetJoypadAnalogInput(&l_stick_angle.x, &l_stick_angle.y, DX_INPUT_PAD1); // 入力状態を取得
}

bool Key::KeyPressed(KEY_TYPE key_type)//押してるとき
{
	if (key[static_cast<int>(key_type)].now_flg)return TRUE;
	else return FALSE;
}

bool Key::KeyUp(KEY_TYPE key_type)//離したとき
{
	if ((!key[static_cast<int>(key_type)].now_flg) && (key[static_cast<int>(key_type)].old_flg))return TRUE;
	else return FALSE;
}

bool Key::KeyDown(KEY_TYPE key_type)//押した瞬間
{
	if ((!key[static_cast<int>(key_type)].old_flg) && (key[static_cast<int>(key_type)].now_flg))return TRUE;
	else return FALSE;
}

DATA Key::GetStickAngle(KEY_TYPE key)
{
	DATA sa = { 0.0f,0.0f };

	if (key == KEY_TYPE::L)
	{
		sa.x = (float)l_stick_angle.x;
		sa.y = (float)l_stick_angle.y;
	}
	else if (key == KEY_TYPE::R)
	{
		sa.x = (float)r_stick_angle.x;
		sa.y = (float)r_stick_angle.y;
	}

	if (/*(sa.x > -50.0f && sa.x < 50.0f) ||*/ (sa.x > 1000.0f) || (sa.x < -1000.0f))sa.x = 0.0f;
	if (/*(sa.y > -50.0f && sa.y < 50.0f) ||*/ (sa.y > 1000.0f) || (sa.y < -1000.0f))sa.y = 0.0f;

	return sa;
}