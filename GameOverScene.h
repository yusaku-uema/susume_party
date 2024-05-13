#include "SceneBase.h"
#include <string>

class GameOverScene : public SceneBase
{
private:
    int gameover_image;  // ゲームオーバー画像
    int transparency;
    int transparencySpeed;
    int imagePosX, imagePosY;

    // テキスト表示用の変数
    char textBuffer[256];  // 表示するテキスト
    int textLength;        // テキストの長さ
    int textIndex;         // 現在表示しているテキストのインデックス
    int draw_x, draw_y;    // テキストの描画位置

public:
    GameOverScene();
    virtual ~GameOverScene();

    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual SCENE_TYPE Update(float delta_time) override;
    virtual void Draw() const override;

    virtual SCENE_TYPE GetNowScene() const override;
    void LoadText(const char* filePath);  // テキストをファイルから読み込む関数
};
