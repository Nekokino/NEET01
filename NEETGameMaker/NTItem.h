#pragma once
#include <NTNameTag.h>
#include <RefNAutoptr.h>
#include <NTTypeParent.h>

class NTItem : public NTNameTag, public RefCounter, public NTTypeParent
{
public:
	std::wstring Output;
	std::wstring Info;
	size_t Price;
	bool Sellable;
public:
	NTItem();
	virtual ~NTItem() = 0;
};