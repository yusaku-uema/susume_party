#pragma once
#include "SceneBase.h"
#include"TalkUi.h"

#define MENU_NUM 4

class TitleScene : public SceneBase
{
private:

    TalkUi talkUi; // TalkUIのインスタンスをメンバ変数として保持

    static const int CHARACTER_COUNT = 4; // キャラクターの数を4に変更
    int characterImages[CHARACTER_COUNT][5];
    int currentFrames[CHARACTER_COUNT];
    int frameCounts[CHARACTER_COUNT];
    int frameWidth;
    int frameHeight;
    int scaleFactor;

    static int scrollX; // 背景のスクロール量を静的メンバーとして定義
    static int logoX; // ロゴのX座標を静的メンバーとして定義
    static int background_images[2]; // 背景画像のハンドルを静的メンバーとして定義
    static int menuX; // 



    int logo_image;//タイトルロゴ

    int menu_image[MENU_NUM][2];//メニュー画像
    int num_image[4];
    int set_menu_image[8];
    int help_image[3]; //ヘルプイメージ

    int input_time;//入力受付時間
    int select_menu;//現在入力しているメニュー
    int help_menu;
    int credit_image;

    bool can_scene_change;//次のシーンに行けるか
    bool help;//ヘルプ画面に行くか
    bool credit;//クレジット
    bool isMenuScrolling;
    int lastAPressTime;
    
  
    int bgm; //BGM
    int move_se; //動くときのSE

    int decision_se;//決定


 


public:
    TitleScene();
    virtual ~TitleScene();

    void Initialize() override;
    void Finalize() override;

    SCENE_TYPE Update(float delta_time) override;
    void Draw() const override;

    SCENE_TYPE GetNowScene() const override;
};
