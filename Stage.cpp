#include"DxLib.h"
#include"Stage.h"

#define DRAW_PLAYER_LOCATION_X 550.0f//����L�����̕\���ʒu

Stage::Stage(Ui* ui) : camera_work(0.0f), stop_time(0.0f), time_count(0.0f)
{
	attack_manager = new AttackManager(this, player_manager, enemy_manager);
	player_manager = new PlayerManager(this, attack_manager, ui);
	enemy_manager = new EnemyManager(this, player_manager, attack_manager);

	
	attack_manager->SetPointer(player_manager, enemy_manager);

	//�w�i�摜
	if (LoadDivGraph("image/Stage/background.png", 4, 1, 4, 2000, 540, back_ground_image) == -1)throw("image/Stage/background.png���ǂݍ��߂܂���\n");

	//�u���b�N�摜
	if (LoadDivGraph("image/Stage/block.png", BLOCK_TYPE_NUM, BLOCK_TYPE_NUM, 1, BLOCK_SIZE, BLOCK_SIZE, block_image) == -1)throw("image/Stage/block.png���ǂݍ��߂܂���\n");

	SetStage();
	OutputDebugString("Stage�R���X�g���N�^�Ă΂�܂����B\n");
}

void Stage::SetStage()
{
	FILE* stage_data = nullptr;//�X�e�[�W�ǂݍ���

	errno_t error_stage_data = fopen_s(&stage_data, "data/stage.txt", "r");
	if (error_stage_data != 0)throw("data/stage.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N
	
	block.reserve(3000);//�u���b�N�̃������̊m��

	//�u���b�N��z�u����
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//���̌J��Ԃ�
		{
			//�u���b�N�̎��
			int block_type;
			fscanf_s(stage_data, "%d", &block_type);

			//�u���b�N�̐���
			if (block_type != -1)
			{
				DATA location = { j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) };

				if (block_type <= 4) block.emplace_back(location, BLOCK_TYPE::SOIL_BLOCK, block_image[block_type]);
				else back_ground_block.emplace_back(BACK_GROUND_BLOCK{ location, block_type });
			}
		}
	}
	block.shrink_to_fit();//�K�v�Ȃ��u���b�N�̃������̉��
	fclose(stage_data);
}

Stage::~Stage()
{
	for (int i = 0; i < 4; i++)DeleteGraph(back_ground_image[i]);
	for (int i = 0; i < 2; i++)DeleteGraph(block_image[i]);

	block.clear();
	block.shrink_to_fit();

	back_ground_block.clear();
	back_ground_block.shrink_to_fit();

	delete player_manager;
	delete enemy_manager;
	delete attack_manager;

	OutputDebugString("Stage�f�X�g���N�^�Ă΂�܂����B\n");
}

bool Stage::Update(float delta_time)
{
	if ((time_count += delta_time) > stop_time)
	{
		time_count = 0.0f;
		stop_time = 0.0f;

		//�v���C���[(�E�҈�s)�̍X�V
		if (player_manager->Update(delta_time))return true;

		//�G�̍X�V
		enemy_manager->Update(delta_time);

		//�U���̍X�V
		attack_manager->Update(delta_time);

		//�G�̍X�V

		SetCameraWork();
	}

	return false;
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
	
	if (player_manager->GetPlayerData()->GetLocation().x > DRAW_PLAYER_LOCATION_X)
	{
		const float camera_work_speed = 5.0f;

		if ((-player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X) > camera_work)
		{
			if ((-player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X) - camera_work > camera_work_speed)camera_work += camera_work_speed;
			else camera_work = -player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X;
		}
		else if ((-player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X) < camera_work)
		{
			if (camera_work - (-player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X) > camera_work_speed)camera_work -= camera_work_speed;
			else camera_work = -player_manager->GetPlayerData()->GetLocation().x + DRAW_PLAYER_LOCATION_X;
		}
	}
	else if ((camera_work += 5.0f) > 0.0f)camera_work = 0.0f;

	camera_work = floorf(camera_work);

	//��ʒ��S���W�v�Z
	center_location_x = -camera_work + SCREEN_CENTER_X;
}

void Stage::SetStopTime(float stop_time)
{
	this->stop_time = stop_time;
}

float Stage::GetCameraWork()const
{
	return camera_work;
}

float Stage::GetCenterLocationX()const
{
	return center_location_x;
}

void Stage::Draw() const
{
	//�w�i�摜�\��

	for (int i = 0; i < 4; i++)
	{
		float back_ground_x = camera_work * (0.02 * (i + 1));
		DrawGraph(back_ground_x, 0, back_ground_image[i], TRUE);
	}

	//�u���b�N�\��
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);

	//�����蔻��̂Ȃ��u���b�N�̕\��
	for (int i = 0; i < back_ground_block.size(); i++)
	{
		DrawRotaGraph(back_ground_block[i].location.x + camera_work, back_ground_block[i].location.y, 1, 0, block_image[back_ground_block[i].type], TRUE);
	}
	
	//�G�̕\��
	enemy_manager->Draw();

	//�v���C���[�\��
	player_manager->Draw();

	

	//�U���i���@�̒e�A�a���A�A�j�\��
	attack_manager->Draw();

	DrawString(0, 0, "LB = �L�����؂�ւ�", 0xffffff);
	DrawString(950,0, "RB = �p�[�e�B�؂藣��", 0xffffff);
	//DrawFormatString(0, 0, 0xffffff, "%d = block_num", block.size());
}