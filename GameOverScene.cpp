#include"GameOverScene.h"
#include"Key.h"
#include"DxLib.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

//����������
void GameOverScene::Initialize()
{
}

//�I��������
void GameOverScene::Finalize()
{
}

//�X�V����
SCENE_TYPE GameOverScene::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::A))return SCENE_TYPE::MAIN;
	return GetNowScene();
}

//�`�揈��
void GameOverScene::Draw() const
{
	DrawString(0, 0, "�Q�[���I�[�o�[", 0xffffff);
}


//���݂̃V�[�������擾
SCENE_TYPE GameOverScene::GetNowScene() const
{
	return SCENE_TYPE::GAME_OVER;
}