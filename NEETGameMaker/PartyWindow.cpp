#include "PartyWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>
#include <InputSystem.h>

PartyWindow::PartyWindow() : CurIndex(0), MoveUnderWindow(false), SelectDetail(false), WinSize(0.0f), LeftWindow01(nullptr)
	,LeftWindow02(nullptr), LeftWindow03(nullptr), LeftWindow04(nullptr), RightWindow(nullptr),
	UnderLowerWindow(nullptr), UnderUpperWindow(nullptr), Cursor(nullptr)
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

	UnderUpperWindow = GetScene()->CreateObject(L"UnderUpperWIndow", UILayer);
	GetNTObject()->AddChild(UnderUpperWindow);
	UnderUpperWindow->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.5625f });

	Autoptr<NTPieceWindow> EquipWindow = UnderUpperWindow->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	
	return true;
}

void PartyWindow::MainUpdate()
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
			MoveUnderWindow = true;
		}
	}
	
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

	if (MoveUnderWindow == true)
	{
		UnderUpperWindow->GetTransform()->SetLocalMove({ 0.0f, 250.0f * TimeSystem::DeltaTime() });
		if (true)
		{

		}
	}

	RightWindow->GetComponent<PartyDetailWindow>()->SetPlayerStatus(CurIndex);
}

void PartyWindow::DbgRender()
{
}