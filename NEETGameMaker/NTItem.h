#pragma once
#include <list>
#include <NTNameTag.h>
#include <RefNAutoptr.h>
#include <NTTypeParent.h>

#include <unordered_map>
class NTItem : public NTNameTag, public RefCounter, public NTTypeParent
{
public:
	static std::unordered_map<std::wstring, Autoptr<NTItem>> ItemData;
	static std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator FindIter;

public:
	static Autoptr<NTItem> FindItem(const wchar_t* _Name);
	static std::list<Autoptr<NTItem>> FindTypeList(const char* _ClassName);
public:
	std::wstring Output;
	std::wstring Info;
	size_t Price;
	bool Sellable;
public:
	NTItem();
	virtual ~NTItem() = 0;
};