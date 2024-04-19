#include"DxLib.h"
#include"Stage.h"

Stage::Stage() : fps(0.0f)
{
	slime = new Slime();
	bird = new Bird();
	for (int i = 0; i < 3; i++)player[i] = new PlayerBase();
	//空画像
	if ((sky_image = LoadGraph("image/Stage/sky.png")) == -1)throw("image/Stage/sky.pngが読み込めません\n");
	//ブロック画像
	if (LoadDivGraph("image/Stage/block.png", 2, 2, 1, 50, 50, block_image) == -1)throw("image/Stage/block.pngが読み込めません\n");

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
			if(block_type != 0)block.emplace_back(DATA{ j * BLOCK_SIZE + (BLOCK_SIZE / 2) , i * BLOCK_SIZE + (BLOCK_SIZE / 2) }, static_cast<BLOCK_TYPE>(block_type), block_image[block_type - 1]);//ブロックの生成
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

	for (int i = 0; i < 3; i++)delete player[i];

	delete slime;
	delete bird;

	OutputDebugString("Stageデストラクタ呼ばれました。\n");
}

void Stage::Update(float delta_time)
{
	player[0]->Update(delta_time, this, nullptr);
	player[1]->Update(delta_time, this, player[0]);
	player[2]->Update(delta_time, this, player[1]);

	slime->Update(delta_time, this);

	fps = 1.0 / delta_time;
	bird->Update(delta_time, this);
}

bool Stage::HitBlock(BoxCollider* bc)const
{
	for (int i = 0; i < block.size(); i++)if (block[i].HitBox(bc))return true;//ブロックに当たった場合trueを返す
	return false;//ブロックに当たらなかった
}

void Stage::Draw() const
{
	DrawGraph(0, 0, sky_image, FALSE);
	for (int i = 0; i < block.size(); i++)block[i].Draw();
	for (int i = 0; i < 3; i++)player[i]->Draw();
	slime->Draw();
	bird->Draw();
	DrawFormatString(0, 0, 0xffffff, "%f", fps);
}