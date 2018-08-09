#include "GameSystem.h"
#include "NTNPC.h"

GameSystem::GAMEMODE GameSystem::GameMode = (GameSystem::GAMEMODE)0;
PlayerStatus GameSystem::PS[CHARA_MAX] = {};
GameSystem::CHARACTER GameSystem::BattleMember[3] = {};
bool GameSystem::TextWindow = false;
bool GameSystem::Inputable = true;
wchar_t GameSystem::TextData[256][256] = {};
bool GameSystem::NextText = false;
int GameSystem::WindowStyle = 0;
NTNPC* GameSystem::TextNPC = nullptr;

void GameSystem::SetNextText(NTNPC * _NPC, bool _Value)
{
	TextNPC = _NPC;
	NextText = _Value;
}

void GameSystem::ActiveText()
{
	TextNPC->ActiveTextEvent();
}

GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}
