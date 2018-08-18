#pragma once
#include <NTLogic.h>

class NTPieceWindow;
class PartyMemWindow : public NTLogic
{
private:
	int Index;
	NTVEC2 WinSize;
	Autoptr<NTPieceWindow> WindowRenderer;
public:
	bool Init(int _Index);
	void MainUpdate() override;
	void DbgUpdate() override;
public:
	PartyMemWindow();
	~PartyMemWindow();
};

