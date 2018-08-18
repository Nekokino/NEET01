#pragma once
#include <NTLogic.h>


class PartyWindow : public NTLogic
{
private:
	NTVEC2 WinSize;
	Autoptr<NTObject> LeftWindow01;
	Autoptr<NTObject> LeftWindow02;
	Autoptr<NTObject> LeftWindow03;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;
public:
	PartyWindow();
	~PartyWindow();
};

