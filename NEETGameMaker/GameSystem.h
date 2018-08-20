#pragma once
#include <Windows.h>
#include "GameValue.h"
#include "NTWeapon.h"
#include "NTArmor.h"
#include "NTHelmet.h"
#include "NTAcc.h"
#include "NTInventory.h"

class NTNPC;
class PlayerStatus // 각각 캐릭터마다 가지고 있을 내용들.
{
public:
	enum EFFECT
	{
		EF_BERSERK, // 물리공격 데미지 1.5배, 받는 물리데미지 2/3
		EF_HASTE, // 스피드 수치 두배
		EF_LIFELINE, // 죽으면 자동부활
		EF_SAFE, // 마법대미지 2/3
		EF_SHIELD, // 물리데미지 2/3
		EF_SERAPH, // 주기적으로 5MP 회복
		EF_CHAOS, // 무작위로 아군 공격
		EF_DARKNESS, // 공격 명중률 감소
		EF_LOCK, // 기술 사용 불가능
		EF_POISON, // 주기적으로 HP감소
		EF_SLEEP, // 일어날때까지 아무것도 못함
		EF_SLOW, // 스피드 수치 반감
		EF_STOP, // 전투 끝날때까지 멈춤
		EF_MAX
	};

	enum ELEMENT
	{
		EM_FIRE,
		EM_WATER,
		EM_LIGHT,
		EM_SHADOW,
		EM_MAX
	};
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
};

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

public:
	GameSystem();
	virtual ~GameSystem() = 0;
};

