#include"DxLib.h"
#include"NpcBase.h"

NpcBase::NpcBase(DATA location, DATA size) : CharacterBase(location, size)
{
    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

NpcBase::~NpcBase()
{
    for (int i = 0; i < 4; i++)DeleteGraph(npc_image[i]);

    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}