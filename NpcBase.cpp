#include"DxLib.h"
#include"NpcBase.h"

NpcBase::NpcBase(DATA location, DATA size) : CharacterBase(location, size)
{
    OutputDebugString("NpcBase�R���X�g���N�^�Ă΂�܂����B\n");
}

NpcBase::~NpcBase()
{
    for (int i = 0; i < 4; i++)DeleteGraph(npc_image[i]);

    OutputDebugString("NpcBase�f�X�g���N�^���Ă΂�܂����B\n");
}