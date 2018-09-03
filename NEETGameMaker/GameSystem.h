#pragma once
#include <Windows.h>
#include "GameValue.h"
#include "NTWeapon.h"
#include "NTArmor.h"
#include "NTHelmet.h"
#include "NTAcc.h"
#include "NTInventory.h"

class PlayerStatus // ���� ĳ���͸��� ������ ���� �����.
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

	int Power; // �������� ���
	int Speed; // �� ���ƿ��� �ӵ�. �Ҹ������θ� �ö�. �������� ��
	int Hit; // ��Ȯ�����ε�. ����� ��ī ���ݷ¿� ����.
	int Evade; // ȸ����
	int Magic; // �������� ���
	int Stamina; // �⺻ ����
	int MagicDef; // �⺻ ��������

	NTWeapon Weapon;
	NTHelmet Helmet;
	NTArmor Armor;
	NTAcc Acc;
	// ������ 4��

	bool Member; // ���� �����ΰ�? (���� �̺�Ʈ�� ���� ����� ��� �����Ѱ�?)
	bool Usable; // ���� ����� �����Ѱ�? (��Ʋ ����� ���� �� �ִ���)
	bool IsFront; // �����ΰ�?
	bool IsBattle; // ���� ����ΰ�?
	size_t BattleOrder; // �׷��ٸ� ���°�ΰ�? (���ζ�� ������ ù��°�ϰ�)
						// ��ų���
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
	// ��ų ���
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
	static CHARACTER BattleMember[3]; // ���� ��������ΰ�? (���δ� 0��°�� �ֵ���)
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

