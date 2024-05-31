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
	ui = new Ui();
	stage = new Stage(ui);
	message = new Message("txt/comment.txt");
}

//�I��������
void GameMainScene::Finalize()
{
	delete ui;
	delete stage;
	delete message;
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	ui->Update();

	stage->Update(delta_time);

	////�f�o�b�N�H
	//if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;
		
	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	stage->Draw();

	ui->Draw();

	if(message != nullptr)message->Draw();
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}