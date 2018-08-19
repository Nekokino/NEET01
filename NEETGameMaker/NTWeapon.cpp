#include "NTWeapon.h"



NTWeapon::NTWeapon() : WeaponType(WT_MAX), Atk(0), Crit(0)
{
	SetType();
}


NTWeapon::~NTWeapon()
{
}
