//#ifndef GAME_OVER_SCENE_H
//#define GAME_OVER_SCENE_H
//
//#include "SceneBase.h"
//#include <string>
//#include <vector>
//
//class GameOverScene : public SceneBase {
//private:
//    int gameover_image;//ゲームオーバー画像
//    DATA  image_location;//ゲームオーバー画像座標
//
//    int frame_count;//経過フレーム
//
//    bool draw_text;
//
//    std::vector<std::string> text_line;
//    
//    float timeSinceFullTransparency = 0; // 透明度が255になってからの時間
//    int frameCount = 0;
//
//public:
//    GameOverScene();
//    ~GameOverScene();
//    void LoadText();
//    void Initialize();
//    void Finalize();
//    SCENE_TYPE Update(float delta_time);
//    void Draw() const;
//    void talk(int x, int y, const char* t, int frameCount) const;
//    SCENE_TYPE GetNowScene() const;
//};
//#endif  // GAME_OVER_SCENE_H
