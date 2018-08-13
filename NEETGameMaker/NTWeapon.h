#pragma once
#include "NTEquip.h"

class NTWeapon : public NTEquip
{
public:
	enum WEAPONTYPE
	{
		WT_Arm, // �κ�
		WT_Bow, // ����
		WT_BroadSword, // ī����
		WT_Fist, // ���̶�
		WT_Gun, // ��ī
		WT_Scythe, // ����
		WT_Sword, // ũ�γ�
		WT_MAX,
	};

	WEAPONTYPE Type;
	size_t Atk;
	size_t Crit;
public:
	NTWeapon();
	~NTWeapon();
};

