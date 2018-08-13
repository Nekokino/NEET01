#pragma once
#include "NTEquip.h"

class NTArmor : public NTEquip
{
public:
	enum ARMORTYPE
	{
		AT_FEMALE,
		AT_MALE,
		AT_MAX
	};

	ARMORTYPE Type;
	size_t Def;
public:
	NTArmor();
	~NTArmor();
};

