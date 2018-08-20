#include "NTInventory.h"


NTInventory::NTInventory()
{
}


NTInventory::~NTInventory()
{
}

void NTInventory::UpdateInventory()
{
	StartIter = Inventory.begin();
	EndIter = Inventory.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->Count == 0)
		{
			StartIter = Inventory.erase(StartIter);
		}
		else
		{
			++StartIter;
		}
	}
}

void NTInventory::InsertItem(NTItem * _Item, int _Count)
{
	StartIter = Inventory.begin();
	EndIter = Inventory.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter)->Item == _Item)
		{
			(*StartIter)->Count += _Count;
			UpdateInventory();
			return;
		}
	}

	InventoryData* NewData = new InventoryData();

	Inventory.push_back(NewData);
	UpdateInventory();
}

NTItem * NTInventory::TakeoutItem(NTItem * _Item, int _Count)
{
	StartIter = Inventory.begin();
	EndIter = Inventory.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter)->Item == _Item)
		{
			(*StartIter)->Count -= _Count;
			UpdateInventory();
			return (*StartIter)->Item;
		}
	}
	UpdateInventory();
	return nullptr;
}

void NTInventory::DumpItem(NTItem * _Item)
{
	StartIter = Inventory.begin();
	EndIter = Inventory.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter)->Item == _Item)
		{
			(*StartIter)->Count = 0;
			UpdateInventory();
			return;
		}
	}
	UpdateInventory();
}


