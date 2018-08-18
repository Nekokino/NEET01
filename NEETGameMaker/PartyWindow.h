#pragma once
#include <NTLogic.h>
#include "PartyMemWindow.h"
#include "PartyGameInfoWindow.h"
#include "PartyDetailWindow.h"

class NTSpRenderer;
class PartyWindow : public NTLogic
{
private:
	int CurIndex;
	bool MoveUnderWindow;
	bool SelectDetail;
	NTVEC2 WinSize;
	Autoptr<NTObject> LeftWindow01;
	Autoptr<NTObject> LeftWindow02;
	Autoptr<NTObject> LeftWindow03;
	Autoptr<NTObject> LeftWindow04;
	Autoptr<NTObject> RightWindow;
	Autoptr<NTObject> UnderUpperWindow;
	Autoptr<NTObject> UnderLowerWindow;

	Autoptr<NTSpRenderer> Cursor;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;
public:
	PartyWindow();
	~PartyWindow();
};

