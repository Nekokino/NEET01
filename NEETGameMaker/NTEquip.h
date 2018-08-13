#pragma once
#include "NTItem.h"
#include "GameValue.h"

class NTEquip : public NTItem
{
public:
	CHARACTER Only;
	bool bSpecial;
	void(*SpecialFunc)(void*);
protected:
	NTEquip();
	virtual ~NTEquip() = 0;
};