#include "GameSystem.h"
#include "NTNPC.h"
#include "NTItem.h"

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
int GameSystem::Gold = 0;
NTInventory GameSystem::GameInventory;
bool GameSystem::BattlePhase = false;
bool GameSystem::BattleReadyPhase = false;

void GameSystem::SetNextText(NTNPC * _NPC, bool _Value)
{
	TextNPC = _NPC;
	NextText = _Value;
}

void GameSystem::ActiveText()
{
	TextNPC->ActiveTextEvent();
}

void GameSystem::BaseSetting()
{

#pragma region BasicData
	PS[CHRONO].CurEXP = 0;
	PS[CHRONO].Element = EM_LIGHT;
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
	lstrcpyW(PS[CHRONO].Name, L"크로노");
	PS[CHRONO].NextEXP = 20;
	PS[CHRONO].Power = 5;
	PS[CHRONO].Speed = 13;
	PS[CHRONO].Stamina = 8;
	PS[CHRONO].Usable = true;
	PS[CHRONO].BattleOrder = 0;

	PS[CHRONO].Weapon = *(Autoptr<NTWeapon>)(NTItem::FindItem(L"WoodSword"));
	PS[CHRONO].Armor = *(Autoptr<NTArmor>)(NTItem::FindItem(L"Tunic"));
	PS[CHRONO].Helmet = *(Autoptr<NTHelmet>)(NTItem::FindItem(L"LeatherHat"));
	PS[CHRONO].Acc = *(Autoptr<NTAcc>)(NTItem::FindItem(L"Bandana"));

	PS[MARU].CurEXP = 0;
	PS[MARU].Element = EM_WATER;
	PS[MARU].Evade = 8;
	PS[MARU].Hit = 9;
	PS[MARU].IsBattle = true;
	PS[MARU].IsFront = false;
	PS[MARU].Level = 1;
	PS[MARU].Magic = 8;
	PS[MARU].MagicDef = 8;
	PS[MARU].MaxHP = 65;
	PS[MARU].CurHP = PS[MARU].MaxHP;
	PS[MARU].MaxMP = 12;
	PS[MARU].CurMP = PS[MARU].MaxMP;
	PS[MARU].Member = true;
	lstrcpyW(PS[MARU].Name, L"마루");
	PS[MARU].NextEXP = 20;
	PS[MARU].Power = 2;
	PS[MARU].Speed = 8;
	PS[MARU].Stamina = 6;
	PS[MARU].Usable = true;
	PS[MARU].BattleOrder = 1;

	PS[MARU].Weapon = *(Autoptr<NTWeapon>)(NTItem::FindItem(L"BronzeCrossbow"));
	PS[MARU].Armor = *(Autoptr<NTArmor>)(NTItem::FindItem(L"Tunic"));
	PS[MARU].Helmet = *(Autoptr<NTHelmet>)(NTItem::FindItem(L"LeatherHat"));
	PS[MARU].Acc = *(Autoptr<NTAcc>)(NTItem::FindItem(L"Ribbon"));

	PS[LUCCA].CurEXP = 20;
	PS[LUCCA].Element = EM_FIRE;
	PS[LUCCA].Evade = 8;
	PS[LUCCA].Hit = 8;
	PS[LUCCA].IsBattle = true;
	PS[LUCCA].IsFront = false;
	PS[LUCCA].Level = 2;
	PS[LUCCA].Magic = 8;
	PS[LUCCA].MagicDef = 10;
	PS[LUCCA].MaxHP = 75;
	PS[LUCCA].CurHP = PS[LUCCA].MaxHP;
	PS[LUCCA].MaxMP = 14;
	PS[LUCCA].CurMP = PS[LUCCA].MaxMP;
	PS[LUCCA].Member = true;
	lstrcpyW(PS[LUCCA].Name, L"루카");
	PS[LUCCA].NextEXP = 80;
	PS[LUCCA].Power = 2;
	PS[LUCCA].Speed = 6;
	PS[LUCCA].Stamina = 6;
	PS[LUCCA].Usable = true;
	PS[LUCCA].BattleOrder = 2;

	PS[LUCCA].Weapon = *(Autoptr<NTWeapon>)(NTItem::FindItem(L"AirGun"));
	PS[LUCCA].Armor = *(Autoptr<NTArmor>)(NTItem::FindItem(L"KarateSuit"));
	PS[LUCCA].Helmet = *(Autoptr<NTHelmet>)(NTItem::FindItem(L"LeatherHat"));
	PS[LUCCA].Acc = *(Autoptr<NTAcc>)(NTItem::FindItem(L"SightScope"));

	PS[KAERU].CurEXP = 0;
	PS[KAERU].Element = EM_WATER;
	PS[KAERU].Evade = 9;
	PS[KAERU].Hit = 9;
	PS[KAERU].IsBattle = false;
	PS[KAERU].IsFront = false;
	PS[KAERU].Level = 5;
	PS[KAERU].Magic = 8;
	PS[KAERU].MagicDef = 9;
	PS[KAERU].MaxHP = 128;
	PS[KAERU].CurHP = PS[LUCCA].MaxHP;
	PS[KAERU].MaxMP = 17;
	PS[KAERU].CurMP = PS[LUCCA].MaxMP;
	PS[KAERU].Member = true;
	lstrcpyW(PS[KAERU].Name, L"카에루");
	PS[KAERU].NextEXP = 20;
	PS[KAERU].Power = 9;
	PS[KAERU].Speed = 11;
	PS[KAERU].Stamina = 14;
	PS[KAERU].Usable = false;
	PS[KAERU].BattleOrder = 0;

	PS[KAERU].Weapon = *(Autoptr<NTWeapon>)(NTItem::FindItem(L"BronzeSword"));
	PS[KAERU].Armor = *(Autoptr<NTArmor>)(NTItem::FindItem(L"BronzeArmor"));
	PS[KAERU].Helmet = *(Autoptr<NTHelmet>)(NTItem::FindItem(L"BronzeHelmet"));
	PS[KAERU].Acc = *(Autoptr<NTAcc>)(NTItem::FindItem(L"PowerGlove"));

#pragma endregion

	BattleMember[0] = CHRONO;
	BattleMember[1] = MARU;
	BattleMember[2] = LUCCA;

	PlayTime = 0;

	std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator StartIter = NTItem::ItemData.begin();
	std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator EndIter = NTItem::ItemData.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		const type_info* Type = StartIter->second->GetType();
		GameInventory.InsertItem(StartIter->second);
	}
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
