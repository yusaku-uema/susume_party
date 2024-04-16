#pragma once

//�V�[�����
enum SCENE_TYPE
{
	TITLE,
	MAIN,
	GAME_OVER,
	ENDING,
	GAME_END
};

//���V�[���N���X
class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase(){}

	//����������
	virtual void Initialize(){}
	//�X�V����
	virtual SCENE_TYPE Update(float delta_time)
	{
		return GetNowScene();
	}
	//�`�揈��
	virtual void Draw() const{}
	//�I��������
	virtual void Finalize(){}

	//���݂̃V�[�������擾
	virtual SCENE_TYPE GetNowScene() const = 0;
};