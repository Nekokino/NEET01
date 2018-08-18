#pragma once
#include "NTItem.h"
#include "GameValue.h"

class NTEquip : public NTItem
{
public:
	bool Only[CHARA_MAX];
	bool bSpecial;
	void(*SpecialFunc)(void*);
protected:
	NTEquip();
	virtual ~NTEquip() = 0;
};