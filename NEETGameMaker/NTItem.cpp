#include "NTItem.h"

std::unordered_map<std::wstring, Autoptr<NTItem>> NTItem::ItemData;

NTItem::NTItem() : Price(0), Sellable(false)
{
}


NTItem::~NTItem()
{
}
