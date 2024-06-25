#include"DxLib.h"
#include"Stage.h"

#define DRAW_PLAYER_LOCATION_X 550.0f//����L�����̕\���ʒu

Stage::Stage() : camera_work(0.0f)
{
	player_manager = new PlayerManager();
	enemy_manager = new EnemyManager();
	attack_manager = new AttackManager();
	npc_manager = new NpcManager();
	event_manager = new EventManager();

	player_manager->Initialize(this, enemy_manager, attack_manager);
	enemy_manager->Initialize(this, player_manager, attack_manager);
	attack_manager->Initialize(this, player_manager, enemy_manager);
	npc_manager->Initialize(this, player_manager);
	event_manager->Initialize(this, player_manager, enemy_manager);

	next_transition = false;

	//�w�i�摜
	if (LoadDivGraph("image/Stage/background.png", 4, 1, 4, 2000, 540, back_ground_image) == -1)throw("image/Stage/background.png���ǂݍ��߂܂���\n");
	//����̔w�i�摜
	if ((back_ground_image[4] = LoadGraph("image/Stage/castlebackground.png")) == -1)throw("image/Stage/castlebackground.png���ǂݍ��߂܂���\n");

	if ((pillar_image = LoadGraph("image/Stage/pillar.png")) == -1)throw("image/Stage/pillar.png���ǂݍ��߂܂���\n");

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
	
	int set_block[STAGE_BLOCK_NUM_Y][STAGE_BLOCK_NUM_X];

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)fscanf_s(stage_data, "%d", &set_block[i][j]);
	}

	fclose(stage_data);

	block.reserve(3000);//�u���b�N�̃������̊m��

	//�u���b�N��z�u����
	for (int i = 0; i < STAGE_BLOCK_NUM_X; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_Y; j++)//���̌J��Ԃ�
		{
			//�u���b�N�̐���
			if (set_block[j][i] != -1)
			{
				DATA location = { (i * BLOCK_SIZE) + (BLOCK_SIZE / 2) - BLOCK_SIZE , j * BLOCK_SIZE + (BLOCK_SIZE / 2) };

				if (set_block[j][i] <= 5) block.emplace_back(location, block_image[set_block[j][i]]);
				else back_ground_block.emplace_back(BACK_GROUND_BLOCK{ location, set_block[j][i] });
			}
		}
	}
	block.shrink_to_fit();//�K�v�Ȃ��u���b�N�̃������̉��
	
}

Stage::~Stage()
{
	for (int i = 0; i < 5; i++)DeleteGraph(back_ground_image[i]);
	for (int i = 0; i < 15; i++)DeleteGraph(block_image[i]);
	DeleteGraph(pillar_image);

	block.clear();
	block.shrink_to_fit();

	back_ground_block.clear();
	back_ground_block.shrink_to_fit();

	delete player_manager;
	delete enemy_manager;
	delete attack_manager;
	delete npc_manager;
	delete event_manager;

	OutputDebugString("Stage�f�X�g���N�^�Ă΂�܂����B\n");
}

bool Stage::Update(float delta_time)
{
	SetCameraWork();

	//�C�x���g�̍X�V
	event_manager->Update(delta_time);

	//NPC�̍X�V
	npc_manager->Update(delta_time);

	//�v���C���[(�E�҈�s)�̍X�V
	if (player_manager->Update(delta_time))return true;

	//�G�̍X�V
	enemy_manager->Update(delta_time);

	//�U���̍X�V
	attack_manager->Update(delta_time);

	if (enemy_manager->NextTransition())next_transition = true;

	return false;
}

bool Stage::HitBlock(BoxCollider* bc)
{
	//�u���b�N�ɓ��������ꍇtrue��Ԃ�
	for (int i = 0; i < block.size(); i++)
	{
		//if (block[i].GetLocation().x > center_location_x + SCREEN_SIZE_X)break;

		if (block[i].GetLocation().x > center_location_x - SCREEN_SIZE_X)
		{
			if (block[i].HitBox(bc))return true;
		}
	}
	//�u���b�N�ɓ�����Ȃ�����
	return false;
}

bool Stage::NextTransition()
{
	return next_transition;
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
	center_location_x = -camera_work + HALF_SCREEN_SIZE_X;
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

	DrawGraph(0 + camera_work, 0, back_ground_image[4], TRUE);

	//�u���b�N�\��
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i].Draw(camera_work))break;
	}

	//�����蔻��̂Ȃ��u���b�N�̕\��
	for (int i = 0; i < back_ground_block.size(); i++)
	{
		DATA draw_location = { back_ground_block[i].location.x + camera_work, back_ground_block[i].location.y };
		if (draw_location.x > SCREEN_SIZE_X + BLOCK_SIZE)break;
		if (draw_location.x >= -BLOCK_SIZE)DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, block_image[back_ground_block[i].type], TRUE);
	}
	
	//�G�̕\��
	enemy_manager->Draw();

	//NPC�̕\��
	npc_manager->Draw();

	//�v���C���[�\��
	player_manager->Draw();

	//�U���i���@�̒e�A�a���A�A�j�\��
	attack_manager->Draw();

	
	DrawGraph(-20 + camera_work, 0, pillar_image, TRUE);
	DrawGraph(730 + camera_work, 0, pillar_image, TRUE);
	DrawGraph(1470 + camera_work, 0, pillar_image, TRUE);

	DrawString(0, 0, "LB = �L�����؂�ւ�", 0xffffff);
	DrawString(850,0, "RB = �p�[�e�B�؂藣��", 0xffffff);
	//DrawFormatString(0, 100, 0xffffff, "%d", count);
}