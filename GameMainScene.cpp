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
	ui = new Ui();
	stage = new Stage(ui);
	message = new Message("txt/comment.txt");
	bgm= LoadSoundMem("bgm/stage.mp3");
}

//�I��������
void GameMainScene::Finalize()
{
	delete ui;
	delete stage;
	delete message;

	StopSoundMem(bgm);
	DeleteSoundMem(bgm);
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{

	if (CheckSoundMem(bgm) != 1)
	{   //SE������Ă��Ȃ�������Đ�
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
	}


	ui->Update();

	// �X�e�[�W�̍X�V����
	if (stage->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	if (stage->NextTransition()) return SCENE_TYPE::GAME_CLEAR;

	// ���b�Z�[�W�̍X�V����
	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	if ((this->delta_time += delta_time) >= 1.0f)
	{
		this->delta_time = 0.0f;
		fps = fps_count;
		fps_count = 0;
	}
	else fps_count++;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	stage->Draw();

	ui->Draw();

	//if(message != nullptr)message->Draw();

	DrawFormatString(500, 0, 0xffffff, "%d", fps);
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}