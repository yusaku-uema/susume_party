#include"TalkUi.h"
#include"DxLib.h"
#include"Key.h"

TalkUi::TalkUi()
{
	if ((window_image = LoadGraph("image/CharTalk/messagewindow7.png")) == -1)throw("image/CharTalk/messagewindow.png���ǂݍ��߂܂���\n");
}

TalkUi::~TalkUi()
{
}

//����������
void TalkUi::Initialize()
{

	message = new Message("txt/comment.txt");
}

void TalkUi::Finalize()
{
	delete message;
}

//�X�V����
SCENE_TYPE TalkUi::Update(float delta_time)
{
	if (Key::KeyDown(KEY_TYPE::B))return SCENE_TYPE::MAIN;


	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	return GetNowScene();//���݂̃V�[���^�C�v��Ԃ�
}

//�`�揈��
void TalkUi::Draw() const
{
	

	if (message != nullptr)message->Draw();

	DrawString(0, 0, "talk", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE TalkUi::GetNowScene() const
{
	return SCENE_TYPE::TALKUI;
}

