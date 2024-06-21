#include "GameClearScene.h"
#include "DxLib.h"
#include "Key.h"

GameClearScene::GameClearScene()
	: hero_frame(0), hero_frame_count(0), hero_x(200), hero_y(400), hero_direction(-1), is_moving(false)
{
	// ���b�Z�[�W�쐬
	message = new Message("txt/gameclear.txt");
}

GameClearScene::~GameClearScene()
{
	delete message; // ���b�Z�[�W�̍폜
}

void GameClearScene::Initialize()
{
	king_image = LoadGraph("image/CharTalk/king.png");
	if (king_image == -1)
	{
		throw("image/CharTalk/king.png���ǂݍ��߂܂���ł����B\n");
	}
	background_image = LoadGraph("image/CharTalk/background.png");
	if (background_image == -1)
	{
		throw("image/CharTalk/background.png���ǂݍ��߂܂���\n");
	}

	// �E�҂̉摜�𕪊����ēǂݍ���
	if (LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, hero_images) == -1)
	{
		throw("image/Player/Hero/walk.png���ǂݍ��߂܂���\n");
	}
	if (LoadDivGraph("image/Player/Hero/wait.png", 5, 5, 1, 50, 50, hero_standby) == -1)
	{
		throw("image/Player/Hero/wait.png���ǂݍ��߂܂���\n");
	}

	clear_image = LoadGraph("image/GameClear/gameclear.png");
	if (clear_image == -1)
	{
		throw("image/GameClear/gameclear.png���ǂݍ��߂܂���\n");
	}
}

void GameClearScene::Finalize()
{
	DeleteGraph(king_image);
	DeleteGraph(background_image);
	DeleteGraph(clear_image); // �Q�[���N���A�摜�̍폜
	for (int i = 0; i < 5; ++i)
	{
		DeleteGraph(hero_images[i]); // �E�҂̕��s�摜�̍폜
		DeleteGraph(hero_standby[i]); // �E�҂̑ҋ@�摜�̍폜
	}
}

SCENE_TYPE GameClearScene::Update(float delta_time)
{

	// ���b�Z�[�W�̍X�V�������Ăяo���Atrue ���Ԃ��ꂽ��V�[���J��
	if (message->Update(delta_time))
	{
		return SCENE_TYPE::TITLE;
	}

	// ���̓t���O
	is_moving = false;


	int move_speed = 5;
	int stick_move_speed = 2; // �X�e�B�b�N���쎞�̈ړ����x

	// �\���L�[�̓��͏���
	if (Key::KeyPressed(KEY_TYPE::LEFT))
	{
		hero_x -= move_speed;
		hero_direction = -1;
		is_moving = true;
	}
	if (Key::KeyPressed(KEY_TYPE::RIGHT))
	{
		hero_x += move_speed;
		hero_direction = 1;
		is_moving = true;
	}
	// ���X�e�B�b�N�̓��͏���
	DATA l_stick = Key::GetStickAngle(KEY_TYPE::L);
	if (l_stick.x < -500)
	{
		hero_x -= stick_move_speed;
		hero_direction = -1;
		is_moving = true;
	}
	if (l_stick.x > 500)
	{
		hero_x += stick_move_speed;
		hero_direction = 1;
		is_moving = true;
	}

	// �E�҂̃A�j���[�V�����t���[�����X�V
	hero_frame_count++;
	if (is_moving)
	{
		if (hero_frame_count >= 10) // 10�t���[�����ƂɃA�j���[�V�������X�V
		{
			hero_frame_count = 0;
			hero_frame = (hero_frame + 1) % 4; // 0����3�̃t���[�����z��
		}
	}
	else
	{
		if (hero_frame_count >= 15) // 15�t���[�����Ƃɑҋ@�A�j���[�V�������X�V
		{
			hero_frame_count = 0;
			hero_frame = (hero_frame + 1) % 4; // 0����3�̃t���[�����z��
		}
	}

	// �E�҂̈ʒu����ʓ��ɐ���
	int hero_width, hero_height;
	GetGraphSize(hero_images[0], &hero_width, &hero_height);

	if (hero_x < 0) hero_x = 0;
	if (hero_x > 1280 - hero_width * 3) hero_x = 1280 - hero_width * 3;
	if (hero_y < 0) hero_y = 0;
	if (hero_y > 720 - hero_height * 3) hero_y = 720 - hero_height * 3; // 720�͉�ʂ̍���


	return GetNowScene();
}


void GameClearScene::Draw() const
{
	DrawGraph(0, 0, background_image, TRUE);

	int king_width, king_height;
	GetGraphSize(king_image, &king_width, &king_height);
	DrawExtendGraph(50, 400, 50 + king_width * 3, 400 + king_height * 3, king_image, TRUE); // �X�P�[���t�@�N�^�[��3


		// �E�҂̉摜�����E���]���ĕ`��
		int hero_width, hero_height;
		GetGraphSize(hero_images[0], &hero_width, &hero_height);
		const int* current_hero_images = is_moving ? hero_images : hero_standby;
		if (hero_direction == 1)
		{
			DrawExtendGraph(hero_x, hero_y, hero_x + hero_width * 3, hero_y + hero_height * 3, current_hero_images[hero_frame], TRUE); // �X�P�[���t�@�N�^�[��3
		}
		else
		{
			DrawExtendGraph(hero_x + hero_width * 3, hero_y, hero_x, hero_y + hero_height * 3, current_hero_images[hero_frame], TRUE); // �X�P�[���t�@�N�^�[��3
		}
	
	DrawGraph(220, 100, clear_image, TRUE);
	message->Draw();
}

SCENE_TYPE GameClearScene::GetNowScene() const
{
	return SCENE_TYPE::GAME_CLEAR;
}
