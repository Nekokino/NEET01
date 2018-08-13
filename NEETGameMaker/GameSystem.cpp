#include "GameSystem.h"
#include "NTNPC.h"

GameSystem::GAMEMODE GameSystem::GameMode = (GameSystem::GAMEMODE)0;
PlayerStatus GameSystem::PS[CHARA_MAX] = {};
CHARACTER GameSystem::BattleMember[3] = {};
bool GameSystem::TextWindow = false;
bool GameSystem::Inputable = true;
wchar_t GameSystem::TextData[256][256] = {};
bool GameSystem::NextText = false;
int GameSystem::WindowStyle = 0;
NTNPC* GameSystem::TextNPC = nullptr;
float GameSystem::PlayTime = 0.0f;

void GameSystem::SetNextText(NTNPC * _NPC, bool _Value)
{
	TextNPC = _NPC;
	NextText = _Value;
}

void GameSystem::ActiveText()
{
	TextNPC->ActiveTextEvent();
}

void GameSystem::BasePlayerSetting()
{
	PS[CHRONO].CurEXP = 0;
	PS[CHRONO].Element = PlayerStatus::EM_LIGHT;
	PS[CHRONO].Evade = 8;
	PS[CHRONO].Hit = 8;
	PS[CHRONO].IsBattle = true;
	PS[CHRONO].IsFront = true;
	PS[CHRONO].Level = 1;
	PS[CHRONO].Magic = 5;
	PS[CHRONO].MagicDef = 2;
	PS[CHRONO].MaxHP = 70;
	PS[CHRONO].CurHP = PS[CHRONO].MaxHP;
	PS[CHRONO].MaxMP = 8;
	PS[CHRONO].CurMP = PS[CHRONO].MaxMP;
	PS[CHRONO].Member = true;
	lstrcpyW(PS[CHRONO].Name, L"∂À¿Ô¿Ã");
	PS[CHRONO].NextEXP = 20;
	PS[CHRONO].Power = 5;
	PS[CHRONO].Speed = 13;
	PS[CHRONO].Stamina = 8;
	PS[CHRONO].Usable = true;
	PS[CHRONO].BattleOrder = 0;

	BattleMember[0] = CHRONO;
}

void GameSystem::TimeUpdate()
{
	PlayTime += TimeSystem::DeltaTime();
}

GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}
