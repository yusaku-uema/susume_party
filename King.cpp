#include"DxLib.h"
#include"King.h"

King::King() : NpcBase(DATA{ 30.0f ,0.0f}, DATA{36.0f,36.0f})
{
    if (LoadDivGraph("image/Npc/king.png", 4, 4, 1, 50, 50, npc_image) == -1)throw("image/Npc/king.pngが読み込めません\n");

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
    DrawRotaGraph(location.x, location.y, 3, 0, npc_image[0], TRUE);
}