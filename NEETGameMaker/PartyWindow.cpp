#include "PartyWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>
#include <InputSystem.h>

PartyWindow::PartyWindow() : CurIndex(0)
{
}


PartyWindow::~PartyWindow()
{
}

bool PartyWindow::Init()
{
	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	LeftWindow01 = GetScene()->CreateObject(L"PartyLeftWindow01", UILayer);
	GetNTObject()->AddChild(LeftWindow01);
	LeftWindow01->AddComponent<PartyMemWindow>(0);

	LeftWindow02 = GetScene()->CreateObject(L"PartyLeftWindow02", UILayer);
	GetNTObject()->AddChild(LeftWindow02);
	LeftWindow02->AddComponent<PartyMemWindow>(1);

	LeftWindow03 = GetScene()->CreateObject(L"PartyLeftWindow03", UILayer);
	GetNTObject()->AddChild(LeftWindow03);
	LeftWindow03->AddComponent<PartyMemWindow>(2);

	LeftWindow04 = GetScene()->CreateObject(L"PartyLeftWindow03", UILayer);
	GetNTObject()->AddChild(LeftWindow04);
	LeftWindow04->AddComponent<PartyGameInfoWindow>();

	RightWindow = GetScene()->CreateObject(L"PartyRightWindow", UILayer);
	GetNTObject()->AddChild(RightWindow);
	RightWindow->AddComponent<PartyDetailWindow>(0);
	return true;
}

void PartyWindow::MainUpdate()
{
	if (InputSystem::IsDown(L"ArrowDown") == true)
	{
		if (CurIndex < 2)
		{
			++CurIndex;
		}
	}

	if (InputSystem::IsDown(L"ArrowUp") == true)
	{
		if (CurIndex > 0)
		{
			--CurIndex;
		}
	}

	RightWindow->GetComponent<PartyDetailWindow>()->SetPlayerStatus(CurIndex);
}

void PartyWindow::DbgRender()
{
}