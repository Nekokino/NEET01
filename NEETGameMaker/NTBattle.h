#pragma once

#include <NTLogic.h>
class NTBattle : public NTLogic
{
private:
	bool bDown;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;
public:
	NTBattle();
	~NTBattle();
};