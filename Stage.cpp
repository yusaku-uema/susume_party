#include"DxLib.h"
#include"Stage.h"

#define DRAW_PLAYER_LOCATION_X 550.0f//操作キャラの表示位置

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

	//背景画像
	if (LoadDivGraph("image/Stage/background.png", 4, 1, 4, 2000, 540, back_ground_image) == -1)throw("image/Stage/background.pngが読み込めません\n");
	//お城の背景画像
	if ((back_ground_image[4] = LoadGraph("image/Stage/castlebackground.png")) == -1)throw("image/Stage/castlebackground.pngが読み込めません\n");

	if ((pillar_image = LoadGraph("image/Stage/pillar.png")) == -1)throw("image/Stage/pillar.pngが読み込めません\n");

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
	
	int set_block[STAGE_BLOCK_NUM_Y][STAGE_BLOCK_NUM_X];

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)fscanf_s(stage_data, "%d", &set_block[i][j]);
	}

	fclose(stage_data);

	block.reserve(3000);//ブロックのメモリの確保

	//ブロックを配置する
	for (int i = 0; i < STAGE_BLOCK_NUM_X; i++)//縦の繰り返し
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_Y; j++)//横の繰り返し
		{
			//ブロックの生成
			if (set_block[j][i] != -1)
			{
				DATA location = { (i * BLOCK_SIZE) + (BLOCK_SIZE / 2) - BLOCK_SIZE , j * BLOCK_SIZE + (BLOCK_SIZE / 2) };

				if (set_block[j][i] <= 5) block.emplace_back(location, block_image[set_block[j][i]]);
				else back_ground_block.emplace_back(BACK_GROUND_BLOCK{ location, set_block[j][i] });
			}
		}
	}
	block.shrink_to_fit();//必要ないブロックのメモリの解放

	max_camera_work = ((STAGE_BLOCK_NUM_X - 1) * BLOCK_SIZE) - SCREEN_SIZE_X;
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

	OutputDebugString("Stageデストラクタ呼ばれました。\n");
}

bool Stage::Update(float delta_time)
{
	SetCameraWork();

	//イベントの更新
	event_manager->Update(delta_time);

	//NPCの更新
	npc_manager->Update(delta_time);

	//プレイヤー(勇者一行)の更新
	if (player_manager->Update(delta_time))return true;

	//敵の更新
	enemy_manager->Update(delta_time);

	//攻撃の更新
	attack_manager->Update(delta_time);

	if (enemy_manager->NextTransition())next_transition = true;

	return false;
}

bool Stage::HitBlock(BoxCollider* bc)
{
	//ブロックに当たった場合trueを返す
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i].GetLocation().x > bc->GetLocation().x + 100.0f)break;

		if (block[i].GetLocation().x > bc->GetLocation().x - 100.0f)
		{
			if (block[i].HitBox(bc))return true;
		}
	}
	//ブロックに当たらなかった
	return false;
}

bool Stage::NextTransition()
{
	return next_transition;
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

	//camera_work = floorf(camera_work);

	if (camera_work < -max_camera_work)camera_work = -max_camera_work;

	//画面中心座標計算
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
	//背景画像表示

	for (int i = 0; i < 4; i++)
	{
		float back_ground_x = camera_work * (0.02 * (i + 1));
		DrawGraph(back_ground_x, 0, back_ground_image[i], TRUE);
	}

	DrawGraph(0 + camera_work, 0, back_ground_image[4], TRUE);

	//ブロック表示
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i].Draw(camera_work))break;
	}

	//当たり判定のないブロックの表示
	for (int i = 0; i < back_ground_block.size(); i++)
	{
		DATA draw_location = { back_ground_block[i].location.x + camera_work, back_ground_block[i].location.y };
		if (draw_location.x > SCREEN_SIZE_X + BLOCK_SIZE)break;
		if (draw_location.x >= -BLOCK_SIZE)DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, block_image[back_ground_block[i].type], TRUE);
	}
	
	//敵の表示
	enemy_manager->Draw();

	//NPCの表示
	npc_manager->Draw();

	//プレイヤー表示
	player_manager->Draw();

	//攻撃（魔法の弾、斬撃、、）表示
	attack_manager->Draw();

	
	DrawGraph(-20 + camera_work, 0, pillar_image, TRUE);
	DrawGraph(730 + camera_work, 0, pillar_image, TRUE);
	DrawGraph(1470 + camera_work, 0, pillar_image, TRUE);

	DrawString(0, 0, "LB = キャラ切り替え", 0xffffff);
	DrawString(850,0, "RB = パーティ切り離し", 0xffffff);
	//DrawFormatString(0, 100, 0xffffff, "%d", count);
}