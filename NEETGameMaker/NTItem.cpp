#include "NTItem.h"

std::unordered_map<std::wstring, Autoptr<NTItem>> NTItem::ItemData;
std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator NTItem::FindIter;

Autoptr<NTItem> NTItem::FindItem(const wchar_t * _Name)
{
	FindIter = ItemData.find(_Name);

	if (FindIter == ItemData.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

std::list<Autoptr<NTItem>> NTItem::FindTypeList(const char* _ClassName)
{
	std::list<Autoptr<NTItem>> ReturnList;
	std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator StartIter = ItemData.begin();
	std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator EndIter = ItemData.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (strcmp(StartIter->second->GetType()->name(), _ClassName) == 0)
		{
			ReturnList.push_back(StartIter->second);
		}
	}

	return ReturnList;
}

NTItem::NTItem() : Price(0), Sellable(false)
{
}


NTItem::~NTItem()
{
}
