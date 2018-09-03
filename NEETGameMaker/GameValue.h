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