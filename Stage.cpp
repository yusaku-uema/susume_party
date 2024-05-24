#include"DxLib.h"
#include"Stage.h"

#define DRAW_PLAYER_LOCATION_X 550.0f//����L�����̕\���ʒu

Stage::Stage(Ui* ui) : camera_work(0.0f)
{
	player_manager = new PlayerManager(this, ui);
	attack_manager = new AttackManager(this);
	enemy_manager = new EnemyManager(this, player_manager);
	
	//��摜
	if ((sky_image = LoadGraph("image/Stage/sky.png")) == -1)throw("image/Stage/sky.png���ǂݍ��߂܂���\n");
	//�u���b�N�摜
	if (LoadDivGraph("image/Stage/block1.png", BLOCK_TYPE_NUM, BLOCK_TYPE_NUM, 1, BLOCK_SIZE, BLOCK_SIZE, block_image) == -1)throw("image/Stage/block.png���ǂݍ��߂܂���\n");

	SetStage();
	OutputDebugString("Stage�R���X�g���N�^�Ă΂�܂����B\n");
}

void Stage::SetStage()
{
	FILE* stage_data = nullptr;//�X�e�[�W�ǂݍ���

	errno_t error_stage_data = fopen_s(&stage_data, "data/stage.txt", "r");
	if (error_stage_data != 0)throw("treasure_data���ǂݍ��߂܂���\n");//�G���[�`�F�b�N
	
	block.reserve(3000);//�u���b�N�̃������̊m��

	//�u���b�N��z�u����
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//���̌J��Ԃ�
		{
			int block_type;
			fscanf_s(stage_data, "%d", &block_type);//�u���b�N�̎�ނ��擾
			if(block_type !=-1)block.emplace_back(DATA{ j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) }, BLOCK_TYPE::SOIL_BLOCK, block_image[block_type]);//�u���b�N�̐���
		}
	}
	block.shrink_to_fit();//�K�v�Ȃ��u���b�N�̃������̉��
	fclose(stage_data);
}

Stage::~Stage()
{
	DeleteGraph(sky_image);
	for (int i = 0; i < 2; i++)DeleteGraph(block_image[i]);

	block.clear();
	block.shrink_to_fit();

	delete player_manager;
	delete enemy_manager;
	delete attack_manager;

	OutputDebugString("Stage�f�X�g���N�^�Ă΂�܂����B\n");
}

void Stage::Update(float delta_time)
{
	//�v���C���[(�E�҈�s)�̍X�V
	player_manager->Update(delta_time);

	//�G�̍X�V
	enemy_manager->Update(delta_time);

	//�U���̍X�V
	attack_manager->Update(delta_time);

	//�G�̍X�V
	
	SetCameraWork();
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	//�u���b�N�ɓ��������ꍇtrue��Ԃ�
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;

	//�u���b�N�ɓ�����Ȃ�����
	return false;
}

void Stage::SetCameraWork()
{
	//�J�������[�N�ݒ�
	
	if (player_manager->GetPlayerLocation().x > DRAW_PLAYER_LOCATION_X)
	{
		const float camera_work_speed = 5.0f;

		if ((-player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X) > camera_work)
		{
			if ((-player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X) - camera_work > camera_work_speed)camera_work += camera_work_speed;
			else camera_work = -player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X;
		}
		else if ((-player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X) < camera_work)
		{
			if (camera_work - (-player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X) > camera_work_speed)camera_work -= camera_work_speed;
			else camera_work = -player_manager->GetPlayerLocation().x + DRAW_PLAYER_LOCATION_X;
		}
	}
	else if ((camera_work += 5.0f) > 0.0f)camera_work = 0.0f;

	camera_work = floorf(camera_work);

	//��ʒ��S���W�v�Z
	center_location_x = -camera_work + SCREEN_CENTER_X;
}

float Stage::GetCameraWork()const
{
	return camera_work;
}

float Stage::GetCenterLocationX()const
{
	return center_location_x;
}

void Stage::AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
	attack_manager->AddAttack(location, size, speed, duration_time, attack_power, attack_image);
}

void Stage::Draw() const
{
	//��̉摜�\��
	DrawGraph(0, 0, sky_image, FALSE);

	//�X�e�[�W�i�u���b�N�Ȃǁj�\��
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);

	//�v���C���[�\��
	player_manager->Draw();

	//�G�̕\��
	enemy_manager->Draw();

	//�U���i���@�̒e�A�a���A�A�j�\��
	attack_manager->Draw();

	DrawString(0, 0, "LB = �L�����؂�ւ�", 0xffffff);
	DrawString(950,0, "RB = �p�[�e�B�؂藣��", 0xffffff);
}