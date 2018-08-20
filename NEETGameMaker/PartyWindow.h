#pragma once
#include <NTLogic.h>
#include "PartyMemWindow.h"
#include "PartyGameInfoWindow.h"
#include "PartyDetailWindow.h"
#include "PartyEquipWindow.h"

class NTSpRenderer;
class PartyWindow : public NTLogic
{
private:
	int CurIndex;
	int CurDetailIndex;
	bool MoveUpUnderWindow;
	bool MoveDownUnderWindow;
	bool SelectDetail;
	NTVEC2 WinSize;
	Autoptr<NTObject> LeftWindow01;
	Autoptr<NTObject> LeftWindow02;
	Autoptr<NTObject> LeftWindow03;
	Autoptr<NTObject> LeftWindow04;
	Autoptr<NTObject> RightWindow;
	Autoptr<NTObject> UnderWindow;

	Autoptr<NTSpRenderer> Cursor;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;

	void PauseRenderer();
	void ResumeRenderer();

	void EnterDetail()
	{
		MoveUpUnderWindow = false;
		SelectDetail = true;
	}

	void GetOutDetail()
	{
		MoveDownUnderWindow = false;
		SelectDetail = false;
	}
public:
	PartyWindow();
	~PartyWindow();
};

