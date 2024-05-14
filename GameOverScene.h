#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "SceneBase.h"
#include <string>
#include <vector>

class GameOverScene : public SceneBase {
private:
    int gameover_image;  // ゲームオーバー画像
    int transparency;
    int transparencySpeed;
    int imagePosX, imagePosY;
    int FileHandle;
    char text[256];
    std::vector<std::string> textLines;
    bool textLoaded = false;
    int frameCount = 0; // フレームカウンタ

    void LoadText();  // テキストファイルを読み込むメソッドの宣言

public:
    GameOverScene();
    virtual ~GameOverScene();

    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual SCENE_TYPE Update(float delta_time) override;
    virtual void Draw() const override;
    virtual SCENE_TYPE GetNowScene() const override;

    void talk(int x, int y, const char* t, int frameCount) const;
};
#endif  // GAME_OVER_SCENE_H
