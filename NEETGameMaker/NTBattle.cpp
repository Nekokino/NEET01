#include "NTBattle.h"

NTBattle::NTBattle() : bDown(false), Speed(0), TurnCount(0.0f), TurnReady(false), BattleReady(false)
{
}


NTBattle::~NTBattle()
{
}

bool NTBattle::Init(int _Speed)
{
	Speed = _Speed;
	return true;
}

void NTBattle::PreUpdate()
{
	if (BattleReady == true)
	{
		if (TurnReady == false)
		{
			if (TurnCount < 100)
			{
				TurnCount += Speed * TimeSystem::DeltaTime();
			}
			else
			{
				TurnReady = true;
			}
		}
	}
}

void NTBattle::MainUpdate()
{
	
}

void NTBattle::DbgRender()
{
}