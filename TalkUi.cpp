#include "TalkUi.h"
#include "DxLib.h"
#include "Key.h"

TalkUi::TalkUi()
{

	// ���b�Z�[�W�쐬
	message = new Message("txt/comment.txt");
	

}

TalkUi::~TalkUi()
{
}

void TalkUi::Initialize()
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

	
}

void TalkUi::Finalize()
{

	DeleteGraph(king_image);
	DeleteGraph(background_image);

	delete message; // ���b�Z�[�W�̍폜

}

SCENE_TYPE TalkUi::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::B))
	{
		return SCENE_TYPE::MAIN;
	}

	message->Update(delta_time);

	return GetNowScene();
}

void TalkUi::Draw() const
{
	
	
	DrawGraph(0, 0, background_image, TRUE);
	int width, height;
	GetGraphSize(king_image, &width, &height);
	DrawExtendGraph(50, 400, 50 + width * 3, 400 + height * 3, king_image, TRUE); // �X�P�[���t�@�N�^�[��3
	message->Draw();


	
}

SCENE_TYPE TalkUi::GetNowScene() const
{
	return SCENE_TYPE::TALKUI;
}
