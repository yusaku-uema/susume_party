#include"GameMainScene.h"
#include"Key.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : stage(nullptr),is_pause(false)
{
}

GameMainScene::~GameMainScene()
{
}

//����������
void GameMainScene::Initialize()
{
	stage = new Stage();
}

//�I��������
void GameMainScene::Finalize()
{
	delete stage;
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	stage->Update(delta_time);

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	stage->Draw();
	DrawString(0, 0, "�Q�[�����C��", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}