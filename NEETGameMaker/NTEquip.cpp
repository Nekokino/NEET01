#include "NTEquip.h"



NTEquip::NTEquip() : bSpecial(false), SpecialFunc(nullptr)
{
	memset(Only, false, sizeof(Only));
}


NTEquip::~NTEquip()
{
}
