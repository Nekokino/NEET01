#pragma once
#include <Windows.h>
#include "GameValue.h"
#include "NTWeapon.h"
#include "NTArmor.h"
#include "NTHelmet.h"
#include "NTAcc.h"
#include "NTInventory.h"

class PlayerStatus // 각각 캐릭터마다 가지고 있을 내용들.
{
public:
	wchar_t Name[32];

	int MaxHP;
	int CurHP;
	int MaxMP;
	int CurMP;
	int CurEXP;
	int NextEXP;

	int Level;
	ELEMENT Element;

	int Power; // 물리공격 계수
	int Speed; // 턴 돌아오는 속도. 소모템으로만 올라감. 레벨관계 무
	int Hit; // 정확도쪽인듯. 마루와 루카 공격력에 영향.
	int Evade; // 회피율
	int Magic; // 마법공격 계수
	int Stamina; // 기본 방어력
	int MagicDef; // 기본 마법방어력

	NTWeapon Weapon;
	NTHelmet Helmet;
	NTArmor Armor;
	NTAcc Acc;
	// 아이템 4개

	bool Member; // 현재 동료인가? (동료 이벤트를 봐서 동료로 사용 가능한가?)
	bool Usable; // 현재 사용이 가능한가? (배틀 멤버에 넣을 수 있는지)
	bool IsFront; // 선두인가?
	bool IsBattle; // 전투 멤버인가?
	size_t BattleOrder; // 그렇다면 몇번째인가? (선두라면 무조건 첫번째일것)
						// 스킬목록
};

class EnemyStatus
{
public:
	int MaxHP;
	int CurHP;
	int Exp;
	int TP;
	int Speed;
	int Def;
	int MDef;

	NTItem* CharmItem;
	// 스킬 목록
};

class NTNPC;
class GameSystem
{
private:
	enum GAMEMODE
	{
		GM_ACTIVE,
		GM_WAIT
	};


private:
	static float PlayTime;
	static GAMEMODE GameMode;
	static PlayerStatus PS[CHARA_MAX];
	static CHARACTER BattleMember[3]; // 누가 전투멤버인가? (선두는 0번째에 있도록)
	static bool TextWindow;
	static bool Inputable;
	static wchar_t TextData[TextMaxIndex][TextMaxBuf];
	static bool NextText;
	static int WindowStyle;
	static NTNPC* TextNPC;
	static int Gold;
	static NTInventory GameInventory;
	static bool BattlePhase;
	static bool BattleReadyPhase;

public:
	static PlayerStatus* GetStatus(CHARACTER _Chara)
	{
		return &PS[_Chara];
	}

	static bool GetTextWindowStatus()
	{
		return TextWindow;
	}

	static void SetTextWindowStatus(bool _Value)
	{
		TextWindow = _Value;
	}

	static void SetInputable(bool _Value)
	{
		Inputable = _Value;
	}

	static bool GetInputable()
	{
		return Inputable;
	}

	static wchar_t* GetText(int _index)
	{
		return TextData[_index];
	}

	static wchar_t* GetTextData(int _index)
	{
		return TextData[_index];
	}

	static void SetText(const wchar_t* _Text, int _index)
	{
		lstrcpyW(TextData[_index], _Text);
	}
	
	static void SetNextText(NTNPC* _NPC, bool _Value);

	static bool GetNextText()
	{
		return NextText;
	}

	static void ClearNPC()
	{
		NextText = false;
		TextNPC = nullptr;
	}

	static void ActiveText();
	
	static int GetWindowStyle()
	{
		return WindowStyle;
	}

	static void SetWindowStyle(int _Style)
	{
		WindowStyle = _Style;
	}

	static PlayerStatus GetPlayerStatus(int _index)
	{
		if (_index >= CHARA_MAX)
		{
			return PS[CHARA_MAX];
		}
		return PS[_index];
	}

	static PlayerStatus* GetBattlememberStatus(int _index)
	{
		if (_index >= 3)
		{
			return &PS[CHARA_MAX];
		}

		return &PS[BattleMember[_index]];
	}

	static CHARACTER GetBattlememberCharacter(int _index)
	{
		if (_index >= 3)
		{
			return CHARA_MAX;
		}

		return BattleMember[_index];
	}

	static void BaseSetting();
	static void TimeUpdate();
	static float GetPlayTime()
	{
		return PlayTime;
	}

	static int GetGold()
	{
		return Gold;
	}

	static NTInventory& GetInventory()
	{
		return GameInventory;
	}

	static void SetBattlePhase(bool _Value)
	{
		BattlePhase = _Value;
		if (BattlePhase == true)
		{
			Inputable = false;
		}
		else
			Inputable = true;
	}

	static void SetBattleReadyPhase(bool _Value)
	{
		BattleReadyPhase = _Value;
	}

	static bool GetBattlePhase()
	{
		return BattlePhase;
	}

	static bool GetBattleReadyPhase()
	{
		return BattleReadyPhase;
	}

public:
	GameSystem();
	virtual ~GameSystem() = 0;
};

