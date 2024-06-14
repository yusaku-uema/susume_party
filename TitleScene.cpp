#include "TitleScene.h"
#include "DxLib.h"
#include "Key.h"

// �X�N���[���X�s�[�h
#define SCROLL_SPEED 1
// ��ʂ̕��ƍ���
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 650

// �w�i�摜�̕��ƍ���
#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define INPUT_ACCEPTANCE_TIME 10

int TitleScene::scrollX = 0;
int TitleScene::logoX = 1300; // ���S�̏����ʒu����ʉE�[�ɐݒ�
int TitleScene::background_images[2] = { -1, -1 }; // �w�i�摜�n���h���̏����l��-1�Ƃ��Ă���
int TitleScene::menuX = 2000; // ���S�̏����ʒu����ʉE�[�ɐݒ�


TitleScene::TitleScene()
	: frameWidth(50), frameHeight(50), scaleFactor(2)
{
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		currentFrames[i] = 0;
		frameCounts[i] = 0;
		for (int j = 0; j < 5; ++j)
		{
			characterImages[i][j] = -1;
		}
	}

	input_time = 0;
	can_scene_change = FALSE;
	select_menu = 0;

	help_menu = 0;
	help = false;
	credit = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	// �L�����N�^�[�摜�̕����ǂݍ���
	LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, characterImages[0]);
	LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, characterImages[1]);
	LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, characterImages[2]);
	LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, characterImages[3]);

	// �w�i�摜�̓ǂݍ���
	if ((background_images[0] = LoadGraph("image/Title/back_ground.png")) == -1 ||
		(background_images[1] = LoadGraph("image/Title/back_ground.png")) == -1)
	{
		throw("image/Title/back_ground\n");
	}

	// �^�C�g�����S�̓ǂݍ���
	if ((logo_image = LoadGraph("image/Title/logo.png")) == -1)
	{
		throw("image/Title/logo.png\n");
	}

	// ���j���[�摜�̓ǂݍ���
	if ((LoadDivGraph("image/Title/menu.png", 8, 2, 4, 450, 75, set_menu_image)) == -1)throw("image/Title/menu.png\n");
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++) menu_image[i][j] = set_menu_image[count++];
	}

}

void TitleScene::Finalize()
{
	// �L�����N�^�[�摜�̍폜
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			DeleteGraph(characterImages[i][j]);
		}
	}

	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)DeleteGraph(menu_image[i][j]);
	}

	for (int i = 0; i < 8; i++)DeleteGraph(set_menu_image[i]);

}

SCENE_TYPE TitleScene::Update(float delta_time)
{
	Key* key;

	// �A�j���[�V�����̃t���[�����X�V
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		frameCounts[i]++;
		if (frameCounts[i] >= 10) // 10�t���[�����ƂɃA�j���[�V�������X�V
		{
			frameCounts[i] = 0;
			currentFrames[i] = (currentFrames[i] + 1) % 4; // �t���[�����ɍ��킹�ă��[�v
		}
	}

	// �X�N���[��
	scrollX -= SCROLL_SPEED;
	if (scrollX <= -BACKGROUND_WIDTH)
	{
		scrollX = 0; // �w�i�摜1���������X�N���[��������A�X�N���[���ʂ����Z�b�g����
	}

	// ���S�̈ړ�
	if (logoX > 0)
	{
		logoX -= 2; // ���S�̃X�N���[���̃X�s�[�h��2�ɂ���
	}

	// ���j���[�̈ړ�
	if (menuX > 640)
	{
		menuX -= 2; //���j���[�̃X�N���[���̃X�s�[�h��2�ɂ��� 
	}
	else
	{
		isMenuScrolling = false; // ���j���[�̃X�N���[�����I���������Ƃ��t���O�ŊǗ�
	}



	//�{�^���������ꂽ��
	if (!isMenuScrolling)
	{
		if (credit == false && help == false)
		{
			
			if (key->KeyDown(KEY_TYPE::B) && select_menu == 0)
			{
				return SCENE_TYPE::MAIN;
			}
			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 1)
			{
				help = true;
			}

			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 2)
			{
				credit = true;
			}

			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 3)
			{
				//DX���C�u�����̎g�p���I������
				DxLib_End();
			}

			else if (key->KeyDown(KEY_TYPE::A))
			{
				can_scene_change = TRUE;
			}

		}
		if (help)
		{

			if (++input_time > INPUT_ACCEPTANCE_TIME)
			{
				if (key->GetStickAngle(KEY_TYPE::L).x > 0)
				{
					if (++help_menu == 3)help_menu = 0;
					input_time = 1;
				}
				else if (key->GetStickAngle(KEY_TYPE::L).x < 0)
				{
					if (--help_menu < 0)help_menu = 2;
					input_time = 1;
				}
			}

			if (key->KeyDown(KEY_TYPE::A))
			{
				input_time = 1;
				help_menu = 0;
				help = false;
			}

		}

		else if (credit)
		{
			if (key->KeyDown(KEY_TYPE::A))
			{
				credit = false;
			}
		}

		else
		{
			//���͎�t��̂�
			if (++input_time > INPUT_ACCEPTANCE_TIME)
			{
				if ((key->GetStickAngle(KEY_TYPE::L).y > 0) || (key->KeyDown(KEY_TYPE::DOWN)))
				{
					if (++select_menu == MENU_NUM)select_menu = 0;
					input_time = 1;
				}
				else if ((key->GetStickAngle(KEY_TYPE::L).y < 0) || (key->KeyDown(KEY_TYPE::UP)))
				{
					if (--select_menu < 0)select_menu = MENU_NUM - 1;
					input_time = 1;
				}
			}

		}
	}

	return GetNowScene(); // ���݂̃V�[���^�C�v��Ԃ�
}

void TitleScene::Draw() const
{

	// �w�i�摜��`��
	DrawGraph(scrollX, 0, background_images[0], TRUE);
	DrawGraph(scrollX + BACKGROUND_WIDTH, 0, background_images[1], TRUE);

	// �^�C�g�����S�̕`��
	DrawGraph(logoX, 50, logo_image, TRUE);

	//���j���[�摜
	for (int i = 0; i < MENU_NUM; i++)
	{
		bool flg = FALSE;
		if (i == select_menu)flg = TRUE;

		DrawRotaGraph(menuX, 300 + (i * 60), 1, 0, menu_image[i][flg], TRUE);
	}

	if (help)
	{
		DrawRotaGraph(640, 360, 1, 0, help_image[help_menu], TRUE);
		DrawRotaGraph(890, 90, 0.3, 0, num_image[0], TRUE, TRUE);
		DrawRotaGraph(970, 90, 0.3, 0, num_image[help_menu + 1], TRUE);
		DrawRotaGraph(1050, 90, 0.3, 0, num_image[0], TRUE);
	}

	if (credit)
	{
		DrawRotaGraph(640, 360, 1, 0, credit_image, TRUE);
	}


	// �L�����N�^�[�̕`��
	int startX = 420; // �L�����N�^�[�̕\���J�n�ʒu�iX���W�j
	int startY = 575; // �L�����N�^�[�̕\���J�n�ʒu�iY���W�j
	int spacing = 100; // �L�����N�^�[�Ԃ̃X�y�[�X

	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		if (characterImages[i][currentFrames[i]] != -1)
		{
			int x = startX + i * spacing; // �L�����N�^�[�̕\���ʒu�iX���W�j
			int y = startY; // �L�����N�^�[�̕\���ʒu�iY���W�j

			// ���݂̃t���[���̕���������`��i�g��`��j
			int scaledWidth = frameWidth * scaleFactor;
			int scaledHeight = frameHeight * scaleFactor;
			DrawExtendGraph(x, y, x + scaledWidth, y + scaledHeight, characterImages[i][currentFrames[i]], TRUE);
		}
	}
}

SCENE_TYPE TitleScene::GetNowScene() const
{
	return SCENE_TYPE::TITLE;
}
