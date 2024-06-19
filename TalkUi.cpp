#include "TalkUi.h"
#include "DxLib.h"
#include "Key.h"

TalkUi::TalkUi()
{

	// メッセージ作成
	message = new Message("txt/gameover.txt");
}

TalkUi::~TalkUi()
{
}

void TalkUi::Initialize()
{
	king_image = LoadGraph("image/CharTalk/king.png");
	if (king_image == -1)
	{
		throw("image/CharTalk/king.pngが読み込めませんでした。\n");
	}
}

void TalkUi::Finalize()
{

	DeleteGraph(king_image);

	delete message; // メッセージの削除

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
	message->Draw();

	int width, height;
	GetGraphSize(king_image, &width, &height);
	DrawExtendGraph(200, 400, 200 + width * 3, 400 + height * 3, king_image, TRUE); // スケールファクターは3

	DrawString(0, 0, "talk", 0xffffff);
}

SCENE_TYPE TalkUi::GetNowScene() const
{
	return SCENE_TYPE::TALKUI;
}
