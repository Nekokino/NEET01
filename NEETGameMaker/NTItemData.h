#pragma once
#include "GameValue.h"

class NTItemData
{
public:
	wchar_t Name[256];
	wchar_t Output[256];
	wchar_t Info[256];
	int Price;
	bool Sellable;
	bool bSpecial;
	int Type;
	int Stat;
	int Crit;
	bool Only[CHARA_MAX];
};

