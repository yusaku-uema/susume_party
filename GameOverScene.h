#include "SceneBase.h"
#include <string>

class GameOverScene : public SceneBase
{
private:
    int gameover_image;  // �Q�[���I�[�o�[�摜
    int transparency;
    int transparencySpeed;
    int imagePosX, imagePosY;

    // �e�L�X�g�\���p�̕ϐ�
    char textBuffer[256];  // �\������e�L�X�g
    int textLength;        // �e�L�X�g�̒���
    int textIndex;         // ���ݕ\�����Ă���e�L�X�g�̃C���f�b�N�X
    int draw_x, draw_y;    // �e�L�X�g�̕`��ʒu

public:
    GameOverScene();
    virtual ~GameOverScene();

    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual SCENE_TYPE Update(float delta_time) override;
    virtual void Draw() const override;

    virtual SCENE_TYPE GetNowScene() const override;
    void LoadText(const char* filePath);  // �e�L�X�g���t�@�C������ǂݍ��ފ֐�
};
