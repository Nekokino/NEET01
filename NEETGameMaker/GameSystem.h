#pragma once
#include <Windows.h>
#include "GameValue.h"

class NTNPC;
class PlayerStatus // ���� ĳ���͸��� ������ ���� �����.
{
public:
	enum EFFECT
	{
		EF_BERSERK, // �������� ������ 1.5��, �޴� ���������� 2/3
		EF_HASTE, // ���ǵ� ��ġ �ι�
		EF_LIFELINE, // ������ �ڵ���Ȱ
		EF_SAFE, // ��������� 2/3
		EF_SHIELD, // ���������� 2/3
		EF_SERAPH, // �ֱ������� 5MP ȸ��
		EF_CHAOS, // �������� �Ʊ� ����
		EF_DARKNESS, // ���� ���߷� ����
		EF_LOCK, // ��� ��� �Ұ���
		EF_POISON, // �ֱ������� HP����
		EF_SLEEP, // �Ͼ������ �ƹ��͵� ����
		EF_SLOW, // ���ǵ� ��ġ �ݰ�
		EF_STOP, // ���� ���������� ����
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

	int Power; // �������� ���
	int Speed; // �� ���ƿ��� �ӵ�. �Ҹ������θ� �ö�. �������� ��
	int Hit; // ��Ȯ�����ε�. ����� ��ī ���ݷ¿� ����.
	int Evade; // ȸ����
	int Magic; // �������� ���
	int Stamina; // �⺻ ����
	int MagicDef; // �⺻ ��������

	// ������ 4��

	bool Member; // ���� �����ΰ�? (���� �̺�Ʈ�� ���� ����� ��� �����Ѱ�?)
	bool Usable; // ���� ����� �����Ѱ�? (��Ʋ ����� ���� �� �ִ���)
	bool IsFront; // �����ΰ�?
	bool IsBattle; // ���� ����ΰ�?
	size_t BattleOrder; // �׷��ٸ� ���°�ΰ�? (���ζ�� ������ ù��°�ϰ�)
};

class GameSystem
{
private:
	enum GAMEMODE
	{
		GM_ACTIVE,
		GM_WAIT
	};
public:
	enum CHARACTER
	{
		CHRONO,
		LUCCA,
		MARU,
		KAERU,
		ROBO,
		EIRA,
		MAOU,
		CHARA_MAX
	};

private:
	static GAMEMODE GameMode;
	static PlayerStatus PS[CHARA_MAX];
	static CHARACTER BattleMember[3]; // ���� ��������ΰ�? (���δ� 0��°�� �ֵ���)
	static bool TextWindow;
	static bool Inputable;
	static wchar_t TextData[TextMaxIndex][TextMaxBuf];
	static bool NextText;
	static int WindowStyle;
	static NTNPC* TextNPC;

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

	static void BasePlayerSetting();

public:
	GameSystem();
	virtual ~GameSystem() = 0;
};

