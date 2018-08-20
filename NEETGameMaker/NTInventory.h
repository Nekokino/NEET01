#pragma once
#include "NTItem.h"

#include <list>

class InventoryData : public RefCounter
{
public:
	NTItem* Item;
	int Count;
};

class NTInventory
{
private:
	std::list<Autoptr<InventoryData>> Inventory;
	std::list<Autoptr<InventoryData>>::iterator StartIter;
	std::list<Autoptr<InventoryData>>::iterator EndIter;

private:
	void UpdateInventory();

public:
	void InsertItem(NTItem* _Item, int _Count = 1);
	NTItem* TakeoutItem(NTItem* _Item, int _Count = 1);
	void DumpItem(NTItem* _Item);
public:
	NTInventory();
	~NTInventory();
};

