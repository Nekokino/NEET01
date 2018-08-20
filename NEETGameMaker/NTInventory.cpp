#include "NTInventory.h"


NTInventory::NTInventory()
{
}


NTInventory::~NTInventory()
{
}

void NTInventory::UpdateInventory()
{
	std::list<Autoptr<InventoryData>>::iterator SIter = Inventory.begin();
	std::list<Autoptr<InventoryData>>::iterator EIter = Inventory.end();

	for (; SIter != EIter;)
	{
		if ((*SIter)->Count == 0)
		{
			SIter = Inventory.erase(SIter);
		}
		else
		{
			++SIter;
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
	NewData->Item = NTItem::FindItem(_Item->GetName());
	NewData->Count = _Count;

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

std::list<Autoptr<InventoryData>> NTInventory::GetTypeList(const char * _ClassName)
{
	std::list<Autoptr<InventoryData>> ReturnList;
	StartIter = Inventory.begin();
	EndIter = Inventory.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (strcmp((*StartIter)->Item->GetType()->name(), _ClassName) == 0)
		{
			ReturnList.push_back((*StartIter));
		}
		
	}

	return ReturnList;
}


