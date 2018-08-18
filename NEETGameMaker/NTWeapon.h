 #pragma once
#include "NTEquip.h"

class NTWeapon : public NTEquip
{
public:
	enum WEAPONTYPE
	{
		WT_ARM, // 로보
		WT_BOW, // 마루
		WT_BROADSWORD, // 카에루
		WT_FIST, // 에이라
		WT_GUN, // 루카
		WT_SCYTHE, // 마왕
		WT_SWORD, // 크로노
		WT_MAX,
	};

	WEAPONTYPE WeaponType;
	size_t Atk;
	size_t Crit;
public:
	NTWeapon();
	~NTWeapon();
};

