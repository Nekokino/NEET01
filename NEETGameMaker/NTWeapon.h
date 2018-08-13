#pragma once
#include "NTEquip.h"

class NTWeapon : public NTEquip
{
public:
	enum WEAPONTYPE
	{
		WT_Arm, // 로보
		WT_Bow, // 마루
		WT_BroadSword, // 카에루
		WT_Fist, // 에이라
		WT_Gun, // 루카
		WT_Scythe, // 마왕
		WT_Sword, // 크로노
		WT_MAX,
	};

	WEAPONTYPE Type;
	size_t Atk;
	size_t Crit;
public:
	NTWeapon();
	~NTWeapon();
};

