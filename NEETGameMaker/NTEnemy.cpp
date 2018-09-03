#include "NTEnemy.h"
#include "GameSystem.h"
#include "NTBattle.h"
#include <NTSpFrameAnimator.h>



NTEnemy::NTEnemy() : Type(ENEMYTYPE::ET_MAX), Status(ENEMYSTATUS::ES_MAX), MoveType(ENEMYWAITMOVE::EWM_MAX), Animator(nullptr), BattleCom(nullptr)
{

}


NTEnemy::~NTEnemy()
{
}

bool NTEnemy::Init()
{
	BattleCom = AddComponent<NTBattle>(0);
	Status = ES_WAIT;

	return true;
}

bool NTEnemy::Init(ENEMYTYPE _EType)
{
	SetEnemyType(_EType);
	BattleCom = AddComponent<NTBattle>(BattleStatus.Speed);
	Status = ES_WAIT;

	return true;
}

void NTEnemy::SetDefaultData()
{
	switch (Type)
	{
	case NTEnemy::ET_GONZALEZ:
		BattleStatus.MaxHP = 76;
		BattleStatus.CurHP = BattleStatus.MaxHP;
		BattleStatus.Exp = 10;
		BattleStatus.TP = 1;
		BattleStatus.Speed = 8;
		BattleStatus.Def = 5;
		BattleStatus.MDef = 5;
		break;
	case NTEnemy::ET_MAX:
	default:
		break;
	}
}


void NTEnemy::MainUpdate()
{
	if (GameSystem::GetBattlePhase() == false)
	{
		return;
	}

	if (Type == ET_GONZALEZ)
	{
		if (Status == ES_WAIT)
		{
			if (BattleCom->IsReady() == false)
			{
				BattleCom->Ready();
			}

			if (GameSystem::GetBattleReadyPhase() == false)
			{
				return;
			}

			NTVEC CurPos = GetNTObject()->GetTransform()->GetLocalPosition();

			switch (MoveType)
			{
			case NTEnemy::EWM_01:
				if (CurPos.y < -90.0f)
				{
					Animator->ChangeAnimation(L"WalkLeft");
					MoveType = EWM_02;
					break;
				}
				GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, -50.0f * TimeSystem::DeltaTime() });
				break;
			case NTEnemy::EWM_02:
				if (CurPos.x < -150.0f)
				{
					Animator->ChangeAnimation(L"WalkUp");
					MoveType = EWM_03;
					break;
				}
				GetNTObject()->GetTransform()->SetLocalMove({ -50.0f * TimeSystem::DeltaTime(), 0.0f });
				break;
			case NTEnemy::EWM_03:
				if (CurPos.y > 100.0f)
				{
					Animator->ChangeAnimation(L"WalkLeft");
					Animator->SideReverse();
					MoveType = EWM_04;
					break;
				}
				GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, 50.0f * TimeSystem::DeltaTime() });
				break;
			case NTEnemy::EWM_04:
				if (CurPos.x > 0.0f)
				{
					Animator->ChangeAnimation(L"WalkDown");
					Animator->SideReverse();
					MoveType = EWM_01;
					break;
				}
				GetNTObject()->GetTransform()->SetLocalMove({ 50.0f * TimeSystem::DeltaTime(), 0.0f });
				break;
			case NTEnemy::EWM_MAX:
				MoveType = EWM_01;
				Animator->ChangeAnimation(L"WalkDown");
				break;
			default:
				break;
			}
		}
		else if (Status == ES_DAMAGE)
		{
			//Animator->ChangeAnimation(L"Damage");
		}
	}
}

void NTEnemy::DbgRender()
{
}

void NTEnemy::SetAnimator(Autoptr<NTSpFrameAnimator> _Animator)
{
	Animator = _Animator;
}

void NTEnemy::Damage()
{
	Status = ES_DAMAGE;
}
