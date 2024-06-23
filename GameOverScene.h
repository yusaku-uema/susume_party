#include "SceneBase.h"

#include"Message.h"

class GameOverScene : public SceneBase {

private:
    int gameover_image;//ゲームオーバー文字画像

    int alpha;//透明度の管理
    int alpha_speed;//透明度の速度
    int bgm;

    int option_yes_image;//「はい」の画像
    int option_no_image;//「いいえ」の画像
    bool option_selected;//洗濯されているオプション(true:はい、false:いいえ)
    bool message_displayed; // メッセージが表示されたかどうかを示すフラグ
  

    Message* message; // メッセージ表示用のインスタンス
   
    
public:
    GameOverScene();
    ~GameOverScene();
    void Initialize()override;
    void Finalize()override;
    SCENE_TYPE Update(float delta_time);
    void Draw() const;


    SCENE_TYPE GetNowScene() const;
};

