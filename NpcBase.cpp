#include"DxLib.h"
#include"NpcBase.h"


NpcBase::NpcBase(DATA location, DATA size, const char* text_data_name) : CharacterBase(location, size)
{
    strcpy_s(this->text_data_name, sizeof(this->text_data_name), text_data_name);
   
    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

NpcBase::~NpcBase()
{
    for (int i = 0; i < 4; i++)DeleteGraph(npc_image[i]);

    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}

const char* NpcBase::GetTextDataName()const
{
    return text_data_name;
}