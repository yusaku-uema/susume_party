#include"TitleScene.h"
#include"DxLib.h"
#include"Key.h"

TitleScene::TitleScene()
{
 
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

