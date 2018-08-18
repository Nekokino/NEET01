#pragma once
#include <NTLogic.h>
#include "GameSystem.h"

class NTSpRenderer;
class NTFontRenderer;
class PartyDetailWindow : public NTLogic
{
private:
	int Index;
	NTVEC2 WinSize;
	PlayerStatus CurStatus;
	CHARACTER CurCharacter;

	Autoptr<NTSpRenderer> CharacterFace;
	Autoptr<NTSpRenderer> CharacterElement;
	Autoptr<NTFontRenderer> CharacterName;
	Autoptr<NTFontRenderer> CharacterLevel;
	Autoptr<NTFontRenderer> EqiupWeapon;
	Autoptr<NTFontRenderer> EquipHelmet;
	Autoptr<NTFontRenderer> EquipArmor;
	Autoptr<NTFontRenderer> EquipAcc;
	Autoptr<NTFontRenderer> Power;
	Autoptr<NTFontRenderer> Hit;
	Autoptr<NTFontRenderer> Speed;
	Autoptr<NTFontRenderer> Magic;
	Autoptr<NTFontRenderer> Evade;
	Autoptr<NTFontRenderer> Stamina;
	Autoptr<NTFontRenderer> MagicDef;
	Autoptr<NTFontRenderer> CurExp;
	Autoptr<NTFontRenderer> NextExp;

	Autoptr<NTSpRenderer> WeaponIcon;

private:
	const wchar_t* IntToString(wchar_t* _Buf, int _Value)
	{
		swprintf_s(_Buf, 32, L"%d", _Value);

		return _Buf;
	}
public:
	bool Init(int _Index);
	void MainUpdate() override;
	void DbgRender() override;

	void SetPlayerStatus(int _Index)
	{
		Index = _Index;
		CurStatus = GameSystem::GetBattlememberStatus(Index);
		CurCharacter = GameSystem::GetBattlememberCharacter(Index);
	}
public:
	PartyDetailWindow();
	~PartyDetailWindow();
};

