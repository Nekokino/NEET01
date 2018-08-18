 #pragma once
#include "NTEquip.h"

class NTWeapon : public NTEquip
{
public:
	enum WEAPONTYPE
	{
		WT_ARM, // �κ�
		WT_BOW, // ����
		WT_BROADSWORD, // ī����
		WT_FIST, // ���̶�
		WT_GUN, // ��ī
		WT_SCYTHE, // ����
		WT_SWORD, // ũ�γ�
		WT_MAX,
	};

	WEAPONTYPE WeaponType;
	size_t Atk;
	size_t Crit;
public:
	NTWeapon();
	~NTWeapon();
};

