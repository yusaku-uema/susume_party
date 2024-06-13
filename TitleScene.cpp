#include"TitleScene.h"
#include"DxLib.h"
#include"Key.h"

#define INPUT_ACCEPTANCE_TIME 10

TitleScene::TitleScene()
{
	input_time = 0;
	
	select_menu = 0;
	help_menu = 0;

	help=false;
	credit = false;

	LoadDivGraph("image/title/menu.png", 8, 2, 4, 600, 100, set_menu_image);
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)menu_image[i][j] = set_menu_image[count++];
	}

 
}

TitleScene::~TitleScene()
{
}

//����������
void TitleScene::Initialize()
{
}

void TitleScene::Finalize()
{
}

//�X�V����
SCENE_TYPE TitleScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::MAIN;
    return GetNowScene();//���݂̃V�[���^�C�v��Ԃ�
}

//�`�揈��
void TitleScene::Draw() const
{
	DrawString(0, 0, "�^�C�g��", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE TitleScene::GetNowScene() const
{
	return SCENE_TYPE::TITLE;
}

