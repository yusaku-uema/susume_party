#include"DxLib.h"
#include"NpcManager.h"

NpcManager::NpcManager()
{
    OutputDebugString("NpcManagerコンストラクタ呼ばれました。\n");
}

NpcManager::~NpcManager()
{
    for (int i = 0; i < npc.size(); i++)delete npc[i];
    npc.clear();
    npc.shrink_to_fit();

    OutputDebugString("NpcManagerデストラクタが呼ばれました。\n");
}

void NpcManager::Update(float delta_time)
{
    for (int i = 0; i < npc.size(); i++)
    {
        npc[i]->Update();
    }
}

void NpcManager::Draw() const
{
    for (int i = 0; i < npc.size(); i++)
    {
        npc[i]->Draw();
    }
}