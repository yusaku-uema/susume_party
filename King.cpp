#include"DxLib.h"
#include"King.h"

King::King(DATA location, DATA size, class Stage* stage, class PlayerManager* player_manager, const char* text_data_name) : NpcBase(location, size, text_data_name)
{
    this->stage = stage;
    this->player_manager = player_manager;

    if (LoadDivGraph("image/Npc/king.png", 4, 4, 1, 29, 43, npc_image) == -1)throw("image/Npc/king.pngが読み込めません\n");

    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

King::~King()
{
    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}

void King::Update()
{
}

void King::Draw()const
{
    DATA draw_location = { location.x + stage->GetCameraWork(), location.y };

    if ((draw_location.x >= -radius.x) && (draw_location.x <= SCREEN_SIZE_X + radius.x))
    {
        DrawRotaGraph(draw_location.x, draw_location.y, 2.0, 0, npc_image[0], TRUE);
    }
}