#pragma once
#include <NTLogic.h>
#include "GameSystem.h"

class NTPieceWindow;
class NTFontRenderer;
class PartyEquipWindow : public NTLogic
{
private:
	NTVEC2 WinSize;

	Autoptr<NTObject> InventoryWindow;
	Autoptr<NTObject> EquipWindow;

	Autoptr<NTPieceWindow> TextWindowRenderer;
	Autoptr<NTPieceWindow> InventoryWindowRenderer;

	Autoptr<NTFontRenderer> EquipType;

	bool bUp;
	bool bDown;
	bool bShow;
	int CurIndex;
	int CurDetailIndex;

	CHARACTER CurChara;
	PlayerStatus* CurPlayer;

public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;

public:
	void SetMoveUp(int _Index)
	{
		bUp = true;
		CurIndex = _Index;
	}

	void SetMoveDown(int _Index)
	{
		bDown = true;
		CurIndex = _Index;
	}

	void SetItemType(int _Index)
	{
		CurDetailIndex = _Index;
		CurChara = GameSystem::GetBattlememberCharacter(CurDetailIndex);
		CurPlayer = GameSystem::GetBattlememberStatus(CurDetailIndex);
	}

private:
	void MoveUp();
	void MoveDown();
public:
	PartyEquipWindow();
	~PartyEquipWindow();
};

