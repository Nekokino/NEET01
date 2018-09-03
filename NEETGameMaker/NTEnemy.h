#pragma once
#include <NTLogic.h>
#include "GameSystem.h"

class NTSpFrameAnimator;
class NTBattle;
class NTEnemy : public NTLogic
{
public:
	enum ENEMYTYPE
	{
		ET_GONZALEZ,
		ET_MAX,
	};

	enum ENEMYSTATUS
	{
		ES_WAIT,
		ES_ATTACK,
		ES_COUNTERATTACK,
		ES_DAMAGE,
		ES_MAX,
	};

	enum ENEMYWAITMOVE
	{
		EWM_01,
		EWM_02,
		EWM_03,
		EWM_04,
		EWM_MAX,
	};

private:
	ENEMYTYPE Type;
	ENEMYSTATUS Status;
	ENEMYWAITMOVE MoveType;
	EnemyStatus BattleStatus;
	EFFECT NowEffect;

	Autoptr<NTSpFrameAnimator> Animator;
	Autoptr<NTBattle> BattleCom;
public:
	bool Init();
	bool Init(ENEMYTYPE _EType);
	void MainUpdate() override;
	void DbgRender() override;
	void SetDefaultData();

	void SetEnemyType(ENEMYTYPE _Type)
	{
		Type = _Type;
		SetDefaultData();
	}
	void SetAnimator(Autoptr<NTSpFrameAnimator> _Animator);
	EnemyStatus* GetStatus()
	{
		return &BattleStatus;
	}
	void Damage();

public:
	NTEnemy();
	~NTEnemy();
};

