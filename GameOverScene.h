#include "SceneBase.h"

#include"Message.h"

class GameOverScene : public SceneBase {

private:
    int gameover_image;//�Q�[���I�[�o�[�����摜

    int alpha;//�����x�̊Ǘ�
    int alpha_speed;//�����x�̑��x
    int bgm;

    int option_yes_image;//�u�͂��v�̉摜
    int option_no_image;//�u�������v�̉摜
    bool option_selected;//���󂳂�Ă���I�v�V����(true:�͂��Afalse:������)
    bool message_displayed; // ���b�Z�[�W���\�����ꂽ���ǂ����������t���O
  

    Message* message; // ���b�Z�[�W�\���p�̃C���X�^���X
   
    
public:
    GameOverScene();
    ~GameOverScene();
    void Initialize()override;
    void Finalize()override;
    SCENE_TYPE Update(float delta_time);
    void Draw() const;


    SCENE_TYPE GetNowScene() const;
};

