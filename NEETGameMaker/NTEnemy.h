#pragma once
#include <NTLogic.h>

class NTEnemy : public NTLogic
{
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;
public:
	NTEnemy();
	~NTEnemy();
};

