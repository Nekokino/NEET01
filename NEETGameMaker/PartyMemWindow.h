#pragma once
#include <NTLogic.h>

#include "GameSystem.h"

class NTPieceWindow;
class NTFontRenderer;
class NTSpRenderer;
class PartyMemWindow : public NTLogic
{
private:
	int Index;
	bool bFontRender;
	PlayerStatus CurPlayer;
	NTVEC2 WinSize;
	Autoptr<NTPieceWindow> WindowRenderer;
	Autoptr<NTFontRenderer> MemberName;
	Autoptr<NTFontRenderer> MemberLevel;
	Autoptr<NTFontRenderer> MemberHP;
	Autoptr<NTFontRenderer> MemberMP;
	Autoptr<NTFontRenderer> MemberAtk;
	Autoptr<NTFontRenderer> MemberDef;

	Autoptr<NTSpRenderer> PlaneAtk;
	Autoptr<NTSpRenderer> PlaneDef;

private:
	void MakeLvString(std::wstring& _gStr)
	{
		_gStr.clear();
		_gStr = L"Lv    ";
		wchar_t Tmp[32];
		swprintf_s(Tmp, L"%d", CurPlayer.Level);
		if (CurPlayer.Level < 10)
		{
			_gStr += L"  ";
		}
		_gStr += Tmp;
	}
	void MakeHMPString(std::wstring& _gStr, int _Use = 0)
	{
		wchar_t Tmp[32];
		_gStr.clear();
		if (_Use == 0)
		{
			swprintf_s(Tmp, L"%d", CurPlayer.CurHP);
			_gStr += Tmp;
			_gStr += L" / ";
			swprintf_s(Tmp, L"%d", CurPlayer.MaxHP);
			_gStr += Tmp;
		}
		else
		{
			swprintf_s(Tmp, L"%d", CurPlayer.CurMP);
			_gStr += Tmp;
			_gStr += L" / ";
			swprintf_s(Tmp, L"%d", CurPlayer.MaxMP);
			_gStr += Tmp;
		}
		
		int tmpint = 11 - lstrlenW(_gStr.c_str());
		switch (tmpint)
		{
		case 3:
			_gStr.insert(0, L"  ");
			break;
		case 4:
			_gStr.insert(0, L"   ");
			break;
		case 5:
			_gStr.insert(0, L"     ");
			break;
		case 6:
			_gStr.insert(0, L"       ");
			break;
		default:
			break;
		}
	}
	void MakeAtkString(std::wstring& _gStr)
	{
		wchar_t Tmp[32];
		_gStr.clear();
		swprintf_s(Tmp, L"%d", CurPlayer.Power + CurPlayer.Weapon.Atk);
		_gStr += Tmp;
	}
	void MakeDefString(std::wstring& _gStr)
	{
		wchar_t Tmp[32];
		_gStr.clear();
		swprintf_s(Tmp, L"%d", CurPlayer.Stamina + CurPlayer.Armor.Def + CurPlayer.Helmet.Def);
		_gStr += Tmp;
	}

	void SetFontRender(bool _Value)
	{
		bFontRender = _Value;
	}
public:
	bool Init(int _Index);
	void MainUpdate() override;
	void DbgUpdate() override;
public:
	PartyMemWindow();
	~PartyMemWindow();
};

