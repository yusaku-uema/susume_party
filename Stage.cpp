#include"DxLib.h"
#include"Stage.h"

#define DRAW_PLAYER_LOCATION_X 550.0f//操作キャラの表示位置

Stage::Stage(Ui* ui) : camera_work(0.0f), stop_time(0.0f), time_count(0.0f)
{
	attack_manager = new AttackManager(this, player_manager, enemy_manager);
	player_manager = new PlayerManager(this, attack_manager, ui);
	enemy_manager = new EnemyManager(this, player_manager, attack_manager);

	
	attack_manager->SetPointer(player_manager, enemy_manager);

	//背景画像
	if (LoadDivGraph("image/Stage/background.png", 4, 1, 4, 2000, 540, back_ground_image) == -1)throw("image/Stage/background.pngが読み込めません\n");

	//ブロック画像
	if (LoadDivGraph("image/Stage/block.png", BLOCK_TYPE_NUM, BLOCK_TYPE_NUM, 1, BLOCK_SIZE, BLOCK_SIZE, block_image) == -1)throw("image/Stage/block.pngが読み込めません\n");

	SetStage();
	OutputDebugString("Stageコンストラクタ呼ばれました。\n");
}

void Stage::SetStage()
{
	FILE* stage_data = nullptr;//ステージ読み込み

	errno_t error_stage_data = fopen_s(&stage_data, "data/stage.txt", "r");
	if (error_stage_data != 0)throw("data/stage.txtが読み込めません\n");//エラーチェック
	
	block.reserve(3000);//ブロックのメモリの確保

	//ブロックを配置する
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)//縦の繰り返し
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)//横の繰り返し
		{
			//ブロックの種類
			int block_type;
			fscanf_s(stage_data, "%d", &block_type);

			//ブロックの生成
			if (block_type != -1)
			{
				DATA location = { j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) };

				if (block_type <= 4) block.emplace_back(location, BLOCK_TYPE::SOIL_BLOCK, block_image[block_type]);
				else back_ground_block.emplace_back(BACK_GROUND_BLOCK{ location, block_type });
			}
		}
	}
	block.shrink_to_fit();//必要ないブロックのメモリの解放
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

	OutputDebugString("Stageデストラクタ呼ばれました。\n");
}

bool Stage::Update(float delta_time)
{
	if ((time_count += delta_time) > stop_time)
	{
		time_count = 0.0f;
		stop_time = 0.0f;

		//プレイヤー(勇者一行)の更新
		if (player_manager->Update(delta_time))return true;

		//敵の更新
		enemy_manager->Update(delta_time);

		//攻撃の更新
		attack_manager->Update(delta_time);

		//敵の更新

		SetCameraWork();
	}

	return false;
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
	//カメラワーク設定
	
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

	//画面中心座標計算
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
	//背景画像表示

	for (int i = 0; i < 4; i++)
	{
		float back_ground_x = camera_work * (0.02 * (i + 1));
		DrawGraph(back_ground_x, 0, back_ground_image[i], TRUE);
	}

	//ブロック表示
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);

	//当たり判定のないブロックの表示
	for (int i = 0; i < back_ground_block.size(); i++)
	{
		DrawRotaGraph(back_ground_block[i].location.x + camera_work, back_ground_block[i].location.y, 1, 0, block_image[back_ground_block[i].type], TRUE);
	}
	
	//敵の表示
	enemy_manager->Draw();

	//プレイヤー表示
	player_manager->Draw();

	

	//攻撃（魔法の弾、斬撃、、）表示
	attack_manager->Draw();

	DrawString(0, 0, "LB = キャラ切り替え", 0xffffff);
	DrawString(950,0, "RB = パーティ切り離し", 0xffffff);
	//DrawFormatString(0, 0, 0xffffff, "%d = block_num", block.size());
}