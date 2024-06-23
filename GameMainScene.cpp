#include"GameMainScene.h"
#include"Key.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : stage(nullptr), is_pause(false)
{
}

GameMainScene::~GameMainScene()
{
}

//����������
void GameMainScene::Initialize()
{
	stage = new Stage();
	bgm= LoadSoundMem("bgm/stage.mp3");
}

//�I��������
void GameMainScene::Finalize()
{
	delete stage;
	
	StopSoundMem(bgm);
	DeleteSoundMem(bgm);
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{

	if (CheckSoundMem(bgm) != 1)
	{   //SE������Ă��Ȃ�������Đ�
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�
	}

	// �X�e�[�W�̍X�V����
	if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	if (stage->NextTransition()) return SCENE_TYPE::GAME_CLEAR;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	stage->Draw();
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}