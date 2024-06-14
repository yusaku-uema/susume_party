#include "TitleScene.h"
#include "DxLib.h"
#include "Key.h"

// スクロールスピード
#define SCROLL_SPEED 1
// 画面の幅と高さ
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 650

// 背景画像の幅と高さ
#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define INPUT_ACCEPTANCE_TIME 10

int TitleScene::scrollX = 0;
int TitleScene::logoX = 1300; // ロゴの初期位置を画面右端に設定
int TitleScene::background_images[2] = { -1, -1 }; // 背景画像ハンドルの初期値は-1としておく
int TitleScene::menuX = 2000; // ロゴの初期位置を画面右端に設定


TitleScene::TitleScene()
	: frameWidth(50), frameHeight(50), scaleFactor(2)
{
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		currentFrames[i] = 0;
		frameCounts[i] = 0;
		for (int j = 0; j < 5; ++j)
		{
			characterImages[i][j] = -1;
		}
	}

	input_time = 0;
	can_scene_change = FALSE;
	select_menu = 0;

	help_menu = 0;
	help = false;
	credit = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	// キャラクター画像の分割読み込み
	LoadDivGraph("image/Player/Monk/walk.png", 5, 5, 1, 50, 50, characterImages[0]);
	LoadDivGraph("image/Player/Wizard/walk.png", 5, 5, 1, 50, 50, characterImages[1]);
	LoadDivGraph("image/Player/Warrior/walk.png", 5, 5, 1, 50, 50, characterImages[2]);
	LoadDivGraph("image/Player/Hero/walk.png", 5, 5, 1, 50, 50, characterImages[3]);

	// 背景画像の読み込み
	if ((background_images[0] = LoadGraph("image/Title/back_ground.png")) == -1 ||
		(background_images[1] = LoadGraph("image/Title/back_ground.png")) == -1)
	{
		throw("image/Title/back_ground\n");
	}

	// タイトルロゴの読み込み
	if ((logo_image = LoadGraph("image/Title/logo.png")) == -1)
	{
		throw("image/Title/logo.png\n");
	}

	// メニュー画像の読み込み
	if ((LoadDivGraph("image/Title/menu.png", 8, 2, 4, 450, 75, set_menu_image)) == -1)throw("image/Title/menu.png\n");
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++) menu_image[i][j] = set_menu_image[count++];
	}

}

void TitleScene::Finalize()
{
	// キャラクター画像の削除
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			DeleteGraph(characterImages[i][j]);
		}
	}

	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)DeleteGraph(menu_image[i][j]);
	}

	for (int i = 0; i < 8; i++)DeleteGraph(set_menu_image[i]);

}

SCENE_TYPE TitleScene::Update(float delta_time)
{
	Key* key;

	// アニメーションのフレームを更新
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		frameCounts[i]++;
		if (frameCounts[i] >= 10) // 10フレームごとにアニメーションを更新
		{
			frameCounts[i] = 0;
			currentFrames[i] = (currentFrames[i] + 1) % 4; // フレーム数に合わせてループ
		}
	}

	// スクロール
	scrollX -= SCROLL_SPEED;
	if (scrollX <= -BACKGROUND_WIDTH)
	{
		scrollX = 0; // 背景画像1枚分だけスクロールしたら、スクロール量をリセットする
	}

	// ロゴの移動
	if (logoX > 0)
	{
		logoX -= 2; // ロゴのスクロールのスピードを2にする
	}

	// メニューの移動
	if (menuX > 640)
	{
		menuX -= 2; //メニューのスクロールのスピードを2にする 
	}
	else
	{
		isMenuScrolling = false; // メニューのスクロールが終了したことをフラグで管理
	}



	//ボタンが押されたら
	if (!isMenuScrolling)
	{
		if (credit == false && help == false)
		{
			
			if (key->KeyDown(KEY_TYPE::B) && select_menu == 0)
			{
				return SCENE_TYPE::MAIN;
			}
			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 1)
			{
				help = true;
			}

			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 2)
			{
				credit = true;
			}

			else if (key->KeyDown(KEY_TYPE::B) && select_menu == 3)
			{
				//DXライブラリの使用を終了する
				DxLib_End();
			}

			else if (key->KeyDown(KEY_TYPE::A))
			{
				can_scene_change = TRUE;
			}

		}
		if (help)
		{

			if (++input_time > INPUT_ACCEPTANCE_TIME)
			{
				if (key->GetStickAngle(KEY_TYPE::L).x > 0)
				{
					if (++help_menu == 3)help_menu = 0;
					input_time = 1;
				}
				else if (key->GetStickAngle(KEY_TYPE::L).x < 0)
				{
					if (--help_menu < 0)help_menu = 2;
					input_time = 1;
				}
			}

			if (key->KeyDown(KEY_TYPE::A))
			{
				input_time = 1;
				help_menu = 0;
				help = false;
			}

		}

		else if (credit)
		{
			if (key->KeyDown(KEY_TYPE::A))
			{
				credit = false;
			}
		}

		else
		{
			//入力受付るのか
			if (++input_time > INPUT_ACCEPTANCE_TIME)
			{
				if ((key->GetStickAngle(KEY_TYPE::L).y > 0) || (key->KeyDown(KEY_TYPE::DOWN)))
				{
					if (++select_menu == MENU_NUM)select_menu = 0;
					input_time = 1;
				}
				else if ((key->GetStickAngle(KEY_TYPE::L).y < 0) || (key->KeyDown(KEY_TYPE::UP)))
				{
					if (--select_menu < 0)select_menu = MENU_NUM - 1;
					input_time = 1;
				}
			}

		}
	}

	return GetNowScene(); // 現在のシーンタイプを返す
}

void TitleScene::Draw() const
{

	// 背景画像を描画
	DrawGraph(scrollX, 0, background_images[0], TRUE);
	DrawGraph(scrollX + BACKGROUND_WIDTH, 0, background_images[1], TRUE);

	// タイトルロゴの描画
	DrawGraph(logoX, 50, logo_image, TRUE);

	//メニュー画像
	for (int i = 0; i < MENU_NUM; i++)
	{
		bool flg = FALSE;
		if (i == select_menu)flg = TRUE;

		DrawRotaGraph(menuX, 300 + (i * 60), 1, 0, menu_image[i][flg], TRUE);
	}

	if (help)
	{
		DrawRotaGraph(640, 360, 1, 0, help_image[help_menu], TRUE);
		DrawRotaGraph(890, 90, 0.3, 0, num_image[0], TRUE, TRUE);
		DrawRotaGraph(970, 90, 0.3, 0, num_image[help_menu + 1], TRUE);
		DrawRotaGraph(1050, 90, 0.3, 0, num_image[0], TRUE);
	}

	if (credit)
	{
		DrawRotaGraph(640, 360, 1, 0, credit_image, TRUE);
	}


	// キャラクターの描画
	int startX = 420; // キャラクターの表示開始位置（X座標）
	int startY = 575; // キャラクターの表示開始位置（Y座標）
	int spacing = 100; // キャラクター間のスペース

	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		if (characterImages[i][currentFrames[i]] != -1)
		{
			int x = startX + i * spacing; // キャラクターの表示位置（X座標）
			int y = startY; // キャラクターの表示位置（Y座標）

			// 現在のフレームの部分だけを描画（拡大描画）
			int scaledWidth = frameWidth * scaleFactor;
			int scaledHeight = frameHeight * scaleFactor;
			DrawExtendGraph(x, y, x + scaledWidth, y + scaledHeight, characterImages[i][currentFrames[i]], TRUE);
		}
	}
}

SCENE_TYPE TitleScene::GetNowScene() const
{
	return SCENE_TYPE::TITLE;
}
