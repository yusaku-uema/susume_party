#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "SceneBase.h"
#include <string>
#include <vector>

class GameOverScene : public SceneBase {
private:
    int gameover_image;
    int transparency;
    int transparencySpeed;
    int imagePosX, imagePosY;
    bool textLoaded = false;
    std::vector<std::string> textLines;
    int FileHandle = 0;
    float timeSinceFullTransparency = 0; // “§–¾“x‚ª255‚É‚È‚Á‚Ä‚©‚ç‚ÌŽžŠÔ
    int frameCount = 0;

public:
    GameOverScene();
    ~GameOverScene();
    void LoadText();
    void Initialize();
    void Finalize();
    SCENE_TYPE Update(float delta_time);
    void Draw() const;
    void talk(int x, int y, const char* t, int frameCount) const;
    SCENE_TYPE GetNowScene() const;
};
#endif  // GAME_OVER_SCENE_H
