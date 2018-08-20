#include "PartyWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>
#include <InputSystem.h>

PartyWindow::PartyWindow() : CurIndex(0), MoveUpUnderWindow(false), SelectDetail(false), WinSize(0.0f), LeftWindow01(nullptr)
	,LeftWindow02(nullptr), LeftWindow03(nullptr), LeftWindow04(nullptr), RightWindow(nullptr),
	Cursor(nullptr), CurDetailIndex(0), MoveDownUnderWindow(false), UnderWindow(nullptr)
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

	Autoptr<NTObject> CursorObj = GetScene()->CreateObject(L"CursorObj", UILayer);
	CursorObj->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 8.0f });
	CursorObj->GetTransform()->SetLocalScale(1.0f);

	Cursor = CursorObj->AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
	Cursor->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Cursor->SetImageIndex(14);
	Cursor->SetSubScale({ 192.0f, 192.0f, 1.0f });
	Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * 0.3375f });

	UnderWindow = GetScene()->CreateObject(L"PartyUnderWindow", UILayer);
	GetNTObject()->AddChild(UnderWindow);
	UnderWindow->AddComponent<PartyEquipWindow>();
	
	return true;
}

void PartyWindow::MainUpdate()
{
	if (MoveUpUnderWindow == false && MoveDownUnderWindow == false)
	{
		if (SelectDetail == false)
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

			if (InputSystem::IsDown(L"Key1") == true)
			{
				MoveUpUnderWindow = true;
			}
		}
		else
		{
			if (InputSystem::IsDown(L"ArrowDown") == true)
			{
				if (CurDetailIndex < 3)
				{
					++CurDetailIndex;
				}
			}

			if (InputSystem::IsDown(L"ArrowUp") == true)
			{
				if (CurDetailIndex > 0)
				{
					--CurDetailIndex;
				}
			}

			if (InputSystem::IsDown(L"Key1") == true)
			{

			}

			if (InputSystem::IsDown(L"Key2") == true)
			{
				MoveDownUnderWindow = true;
			}
		}
	}
	
	if (SelectDetail == false)
	{
		Cursor->SetColor(1.0f);
		switch (CurIndex)
		{
		case 0:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * 0.3375f });
			break;
		case 1:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * 0.1125f });
			break;
		case 2:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * -0.1125f });
			break;
		default:
			break;
		}
	}
	else
	{
		Cursor->SetColor(1.0f);
		if (CurDetailIndex == 0)
		{
			Cursor->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.13f });
		}
		else if (CurDetailIndex == 1)
		{
			Cursor->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.08f });
		}
		else if (CurDetailIndex == 2)
		{
			Cursor->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.03f });
		}
		else if (CurDetailIndex == 3)
		{
			Cursor->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * -0.02f });
		}
	}

	if (MoveUpUnderWindow == true)
	{
		Cursor->SetColor({ 0.0f });
		UnderWindow->GetComponent<PartyEquipWindow>()->SetMoveUp(CurIndex);
		PauseRenderer();
	}

	if (MoveDownUnderWindow == true)
	{
		Cursor->SetColor({ 0.0f });
		UnderWindow->GetComponent<PartyEquipWindow>()->SetMoveDown(CurIndex);
	}

	RightWindow->GetComponent<PartyDetailWindow>()->SetPlayerStatus(CurIndex);

	if (SelectDetail == true)
	{
		UnderWindow->GetComponent<PartyEquipWindow>()->SetItemType(CurDetailIndex);
	}
}

void PartyWindow::DbgRender()
{
}

void PartyWindow::PauseRenderer()
{
	if (CurIndex == 0)
	{
		LeftWindow02->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow03->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->PauseRender();
	}
	else if (CurIndex == 1)
	{
		LeftWindow01->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow03->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->PauseRender();
	}
	else if (CurIndex == 2)
	{
		LeftWindow01->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow02->GetComponent<PartyMemWindow>()->PauseRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->PauseRender();
	}
}

void PartyWindow::ResumeRenderer()
{
	if (CurIndex == 0)
	{
		LeftWindow02->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow03->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->ResumeRender();
	}
	else if (CurIndex == 1)
	{
		LeftWindow01->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow03->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->ResumeRender();
	}
	else if (CurIndex == 2)
	{
		LeftWindow01->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow02->GetComponent<PartyMemWindow>()->ResumeRender();
		LeftWindow04->GetComponent<PartyGameInfoWindow>()->ResumeRender();
	}
}

