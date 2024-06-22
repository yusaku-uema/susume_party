#include"DxLib.h"
#include"NpcBase.h"

NpcBase::NpcBase(DATA location, DATA size) : CharacterBase(location, size)
{
    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

NpcBase::~NpcBase()
{
    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}