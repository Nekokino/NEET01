#pragma once
#include "NTItem.h"
class NTConsume : public NTItem
{
public:
	void(*Effect)(void*);
public:
	NTConsume();
	~NTConsume();
};

