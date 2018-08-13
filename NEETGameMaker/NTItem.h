#pragma once
#include <NTNameTag.h>
#include <RefNAutoptr.h>
#include <NTTypeParent.h>

#include <unordered_map>
class NTItem : public NTNameTag, public RefCounter, public NTTypeParent
{
public:
	static std::unordered_map<std::wstring, Autoptr<NTItem>> ItemData;
public:
	std::wstring Output;
	std::wstring Info;
	size_t Price;
	bool Sellable;
public:
	NTItem();
	virtual ~NTItem() = 0;
};