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

	int ASD;
protected:
	NTItem();
	virtual ~NTItem() = 0;
};