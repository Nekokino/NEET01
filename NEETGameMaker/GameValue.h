#pragma once
#define DefaultFrameSpeed 0.2f
#define DFS DefaultFrameSpeed

#define PlayerLayer 0
#define NPCLayer 1
#define EventLayer 5
#define UILayer 100

#define TextMaxIndex 256
#define TextMaxBuf 256

#define Floor1 NTVEC{10.0f, 10.0f, 10.0f, 255.0f}
#define Floor2 NTVEC{20.0f, 20.0f, 20.0f, 255.0f}
#define Floor3 NTVEC{30.0f, 30.0f, 30.0f, 255.0f}
#define Floor4 NTVEC{40.0f, 40.0f, 40.0f, 255.0f}
#define Floor5 NTVEC{50.0f, 50.0f, 50.0f, 255.0f}

#define Stair1 NTVEC{15.0f, 15.0f, 15.0f, 255.0f}
#define Stair2 NTVEC{25.0f, 25.0f, 25.0f, 255.0f}
#define Stair3 NTVEC{35.0f, 35.0f, 35.0f, 255.0f}
#define Stair4 NTVEC{45.0f, 45.0f, 45.0f, 255.0f}

#define PartyWindowFirstPos NTVEC2{ WinSize.x * -0.27f, WinSize.y * 0.3375f }
#define PartyWindowSecondPos NTVEC2{ WinSize.x * -0.27f, WinSize.y * 0.1125f }
#define PartyWindowThirdPos NTVEC2{ WinSize.x * -0.27f, WinSize.y * -0.1125f }
#define PartyWindowFourthPos NTVEC2{ WinSize.x * -0.27f, WinSize.y * -0.3375f }

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