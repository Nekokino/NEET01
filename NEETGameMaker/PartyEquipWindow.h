#pragma once
#include <NTLogic.h>
#include <vector>
#include <list>

#include "GameSystem.h"
#include "NTInventory.h"

class NTPieceWindow;
class NTFontRenderer;
class NTItem;
class PartyEquipWindow : public NTLogic
{
private:
	NTVEC2 WinSize;

	Autoptr<NTObject> InventoryWindow;
	Autoptr<NTObject> EquipWindow;

	Autoptr<NTPieceWindow> TextWindowRenderer;
	Autoptr<NTPieceWindow> InventoryWindowRenderer;

	Autoptr<NTFontRenderer> EquipType;
	std::vector<Autoptr<NTFontRenderer>> Inventory;

	std::list<Autoptr<InventoryData>> TypeInventory;

	bool bUp;
	bool bDown;
	bool bShow;
	int CurIndex;
	int CurDetailIndex;
	int InventoryScroll;
	int* InventoryIndex;

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
		
	}

	void SetPlayer(int _Index)
	{
		CurChara = GameSystem::GetBattlememberCharacter(_Index);
		CurPlayer = GameSystem::GetBattlememberStatus(_Index);
	}

	void SetInventoryIndex(int* _Index)
	{
		InventoryIndex = _Index;
	}

	int GetShowInventorySize()
	{
		return (int)TypeInventory.size();
	}

	void ChangeEquip();

	void PauseRender();
	void ResumeRender();

private:
	void MoveUp();
	void MoveDown();
public:
	PartyEquipWindow();
	~PartyEquipWindow();
};

