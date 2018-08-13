#pragma once
#include "NTItem.h"
#include "GameValue.h"

class NTEquip : public NTItem
{
public:
	CHARACTER Only;
protected:
	NTEquip();
	virtual ~NTEquip() = 0;
};