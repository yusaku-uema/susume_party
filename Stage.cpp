#include"DxLib.h"
#include"Stage.h"

Stage::Stage() : fps(0.0f), camera_work(0.0f)
{
	player_manager = new PlayerManager();
	slime = new Slime();
	bird = new Bird();
	
	//��摜
	if ((sky_image = LoadGraph("image/Stage/sky.png")) == -1)throw("image/Stage/sky.png���ǂݍ��߂܂���\n");
	//�u���b�N�摜
	if (LoadDivGraph("image/Stage/block.png", 2, 2, 1, 50, 50, block_image) == -1)throw("image/Stage/block.png���ǂݍ��߂܂���\n");

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
			if(block_type != 0)block.emplace_back(DATA{ j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) }, static_cast<BLOCK_TYPE>(block_type), block_image[block_type - 1]);//�u���b�N�̐���
		}
	}
	block.shrink_to_fit();//�K�v�Ȃ��u���b�N�̃������̉��
	fclose(stage_data);
}

void Stage::Initialize()
{
}

Stage::~Stage()
{
	DeleteGraph(sky_image);
	for (int i = 0; i < 2; i++)DeleteGraph(block_image[i]);

	block.clear();
	block.shrink_to_fit();

	delete slime;
	delete bird;

	OutputDebugString("Stage�f�X�g���N�^�Ă΂�܂����B\n");
}

void Stage::Update(float delta_time)
{
	player_manager->Update(delta_time, this);

	slime->Update(delta_time, this);

	fps = 1.0 / delta_time;
	bird->Update(delta_time, this);

	SetCameraWork();
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;//�u���b�N�ɓ��������ꍇtrue��Ԃ�
	return false;//�u���b�N�ɓ�����Ȃ�����
}

void Stage::SetCameraWork()
{
	//�J�������[�N
	if (player_manager->GetPlayerLocation().x > 350.0f)
	{
		const float camera_work_speed = 5.0f;

		if ((-player_manager->GetPlayerLocation().x + 350.0f) > camera_work)
		{
			if ((-player_manager->GetPlayerLocation().x + 350.0f) - camera_work > camera_work_speed)camera_work += camera_work_speed;
			else camera_work = -player_manager->GetPlayerLocation().x + 350.0f;
		}
		else if ((-player_manager->GetPlayerLocation().x + 350.0f) < camera_work)
		{
			if (camera_work - (-player_manager->GetPlayerLocation().x + 350.0f) > camera_work_speed)camera_work -= camera_work_speed;
			else camera_work = -player_manager->GetPlayerLocation().x + 350.0f;
		}
	}
	else camera_work = 0.0f;

	camera_work = floorf(camera_work);
}

void Stage::Draw() const
{
	DrawGraph(0, 0, sky_image, FALSE);
	slime->Draw();
	bird->Draw();

	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);
	player_manager->Draw(camera_work);
	DrawFormatString(0, 0, 0xffffff, "%f", fps);
}