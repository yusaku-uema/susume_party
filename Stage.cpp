#include"DxLib.h"
#include"Stage.h"

Stage::Stage() : fps(0.0f), camera_work(0.0f)
{
	player_manager = new PlayerManager();
	attack_manager = new AttackManager();
	slime = new Slime();
	bird = new Bird();
	flower = new Flower();
	fairy = new Fairy();

	//空画像
	if ((sky_image = LoadGraph("image/Stage/sky.png")) == -1)throw("image/Stage/sky.pngが読み込めません\n");
	//ブロック画像
	if (LoadDivGraph("image/Stage/block1.png", BLOCK_TYPE_NUM, BLOCK_TYPE_NUM, 1, BLOCK_SIZE, BLOCK_SIZE, block_image) == -1)throw("image/Stage/block.pngが読み込めません\n");

	SetStage();
	OutputDebugString("Stageコンストラクタ呼ばれました。\n");
}

void Stage::SetStage()
{
	FILE* stage_data = nullptr;//ステージ読み込み

	errno_t error_stage_data = fopen_s(&stage_data, "data/stage.txt", "r");
	if (error_stage_data != 0)throw("treasure_dataが読み込めません\n");//エラーチェック
	
	block.reserve(3000);//ブロックのメモリの確保

	//ブロックを配置する
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//縦の繰り返し
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//横の繰り返し
		{
			int block_type;
			fscanf_s(stage_data, "%d", &block_type);//ブロックの種類を取得
			if(block_type !=-1)block.emplace_back(DATA{ j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) }, BLOCK_TYPE::SOIL_BLOCK, block_image[block_type]);//ブロックの生成
		}
	}
	block.shrink_to_fit();//必要ないブロックのメモリの解放
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

	delete player_manager;
	delete attack_manager;
	delete slime;
	delete bird;
	delete flower;

	OutputDebugString("Stageデストラクタ呼ばれました。\n");
}

void Stage::Update(float delta_time)
{
	//攻撃の更新
	attack_manager->Update(delta_time, this);

	//プレイヤー(勇者一行)の更新
	player_manager->Update(delta_time, this);

	//敵の更新
	slime->Update(delta_time, this,player_manager);
	flower->Update(delta_time, this, player_manager);
	bird->Update(delta_time, this, player_manager);
	fairy->Update(delta_time, this, player_manager);

	fps = 1.0 / delta_time;
	
	SetCameraWork();
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	//ブロックに当たった場合trueを返す
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;

	//ブロックに当たらなかった
	return false;
}

void Stage::SetCameraWork()
{
	//カメラワーク
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

void Stage::AddAttack(DATA location, DATA size, DATA speed, float duration_time, int attack_power, int attack_image)
{
	attack_manager->AddAttack(location, size, speed, duration_time, attack_power, attack_image);
}

void Stage::Draw() const
{
	//空の画像表示
	DrawGraph(0, 0, sky_image, FALSE);

	//ステージ（ブロックなど）表示
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);

	//敵の表示
	slime->Draw(camera_work);
	bird->Draw(camera_work);
	flower->Draw(camera_work);
	fairy->Draw(camera_work);

	//プレイヤー表示
	player_manager->Draw(camera_work);

	//攻撃（魔法の弾、斬撃、、）表示
	attack_manager->Draw(camera_work);

	DrawFormatString(0, 0, 0xffffff, "%f", fps);
}