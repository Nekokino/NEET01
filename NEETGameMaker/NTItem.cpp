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

NTItem::NTItem() : Price(0), Sellable(false)
{
}


NTItem::~NTItem()
{
}
