#pragma once

#include <NTLogic.h>
class NTBattle : public NTLogic
{
private:
	bool bDown;
	bool BattleReady;
	bool TurnReady;
	int Speed;
	float TurnCount;
public:
	bool Init(int _Speed);
	void PreUpdate() override;
	void MainUpdate() override;
	void DbgRender() override;

	void Ready()
	{
		BattleReady = true;
	}

	void Reset()
	{
		BattleReady = false;
	}

	bool IsReady()
	{
		return BattleReady;
	}

	float GetCount()
	{
		return TurnCount;
	}

	bool IsTurn()
	{
		return TurnReady;
	}
public:
	NTBattle();
	~NTBattle();
};