#include "PartyMemWindow.h"

#include "NTPieceWindow.h"


#include <NTSpRenderer.h>
#include <NTFontRenderer.h>
#include <NTWinShortCut.h>




PartyMemWindow::PartyMemWindow() : bFontRender(true), Index(0), WinSize(0.0f), WindowRenderer(nullptr),
	MemberName(nullptr), MemberLevel(nullptr), MemberHP(nullptr), MemberMP(nullptr), MemberAtk(nullptr),
	MemberDef(nullptr), PlaneAtk(nullptr), PlaneDef(nullptr)
{

}


PartyMemWindow::~PartyMemWindow()
{
}

std::wstring GlobalString;
void PartyMemWindow::PauseRender()
{
	MemberName->SetUpdate(false);
	MemberLevel->SetUpdate(false);
	MemberHP->SetUpdate(false);
	MemberMP->SetUpdate(false);
	MemberAtk->SetUpdate(false);
	MemberDef->SetUpdate(false);
	PlainHP->SetUpdate(false);
	PlainMP->SetUpdate(false);

	PlaneAtk->SetUpdate(false);
	PlaneDef->SetUpdate(false);
}
void PartyMemWindow::ResumeRender()
{
	MemberName->SetUpdate(true);
	MemberLevel->SetUpdate(true);
	MemberHP->SetUpdate(true);
	MemberMP->SetUpdate(true);
	MemberAtk->SetUpdate(true);
	MemberDef->SetUpdate(true);
	PlainHP->SetUpdate(true);
	PlainMP->SetUpdate(true);

	PlaneAtk->SetUpdate(true);
	PlaneDef->SetUpdate(true);
}
bool PartyMemWindow::Init(int _Index)
{
	Index = _Index;
	if (Index >= 3)
	{
		Index = -1;
		return false;
	}
	CurPlayer = GameSystem::GetBattlememberStatus(Index);

	

	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	WindowRenderer = GetNTObject()->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	switch (Index)
	{
	case 0:
		GetNTObject()->GetTransform()->SetLocalPosition(PartyWindowFirstPos);
		break;
	case 1:
		GetNTObject()->GetTransform()->SetLocalPosition(PartyWindowSecondPos);
		break;
	case 2:
		GetNTObject()->GetTransform()->SetLocalPosition(PartyWindowThirdPos);
		break;
	default:
		break;
	}

	if (CurPlayer->Level == 0)
	{
		return true;
	}
	

	MemberName = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberName->SetColor(255, 255, 255, 255);
	MemberName->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberName->SetSize(25.0f);
	MemberName->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberName->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MemberName->SetString(CurPlayer->Name);

	MemberLevel = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberLevel->SetColor(255, 255, 255, 255);
	MemberLevel->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberLevel->SetSize(25.0f);
	MemberLevel->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberLevel->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MakeLvString(GlobalString);
	MemberLevel->SetString(GlobalString.c_str());

	PlainHP = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainHP->SetColor(255, 255, 255, 255);
	PlainHP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainHP->SetSize(25.0f);
	PlainHP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainHP->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainHP->SetString(L"HP");

	MemberHP = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberHP->SetColor(255, 255, 255, 255);
	MemberHP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberHP->SetSize(25.0f);
	MemberHP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberHP->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MakeHMPString(GlobalString);
	MemberHP->SetString(GlobalString.c_str());

	PlainMP = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainMP->SetColor(255, 255, 255, 255);
	PlainMP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainMP->SetSize(25.0f);
	PlainMP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainMP->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainMP->SetString(L"MP");

	MemberMP = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberMP->SetColor(255, 255, 255, 255);
	MemberMP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberMP->SetSize(25.0f);
	MemberMP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberMP->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MakeHMPString(GlobalString, 1);
	MemberMP->SetString(GlobalString.c_str());

	PlaneAtk = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneAtk->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneAtk->SetSubPivot({ -WinSize.x * 0.115f, -WinSize.y * 0.065f });
	PlaneAtk->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	MemberAtk = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberAtk->SetColor(255, 255, 255, 255);
	MemberAtk->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberAtk->SetSize(25.0f);
	MemberAtk->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberAtk->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MakeAtkString(GlobalString);
	MemberAtk->SetString(GlobalString.c_str());

	PlaneDef = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneDef->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneDef->SetSubPivot({ WinSize.x * 0.025f, -WinSize.y * 0.065f });
	PlaneDef->SetImageIndex(14);
	PlaneDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	MemberDef = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MemberDef->SetColor(255, 255, 255, 255);
	MemberDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MemberDef->SetSize(25.0f);
	MemberDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MemberDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	MakeDefString(GlobalString);
	MemberDef->SetString(GlobalString.c_str());

	if (Index == -1)
	{
		PlaneAtk->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		PlaneDef->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	}

	switch (Index)
	{
	case 0:
		MemberName->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f });
		MemberLevel->SetSubPivot({ WinSize.x * 0.275f, WinSize.y * 0.065f});
		PlainHP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 30.0f});
		PlainMP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 60.0f });
		MemberHP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 30.0f });
		MemberMP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 60.0f });
		MemberAtk->SetSubPivot({ WinSize.x * 0.175f, WinSize.y * 0.21f });
		MemberDef->SetSubPivot({ WinSize.x * 0.325f, WinSize.y * 0.21f });
		break;
	case 1:
		MemberName->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.29f });
		MemberLevel->SetSubPivot({ WinSize.x * 0.275f, WinSize.y * 0.29f });
		PlainHP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.29f + 30.0f });
		PlainMP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.29f + 60.0f });
		MemberHP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.29f + 30.0f });
		MemberMP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.29f + 60.0f });
		MemberAtk->SetSubPivot({ WinSize.x * 0.175f, WinSize.y * 0.435f });
		MemberDef->SetSubPivot({ WinSize.x * 0.325f, WinSize.y * 0.435f });
		break;
	case 2:
		MemberName->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.515f });
		MemberLevel->SetSubPivot({ WinSize.x * 0.275f, WinSize.y * 0.515f });
		PlainHP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.515f + 30.0f });
		PlainMP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.515f + 60.0f });
		MemberHP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.515f + 30.0f });
		MemberMP->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.515f + 60.0f });
		MemberAtk->SetSubPivot({ WinSize.x * 0.175f, WinSize.y * 0.66f });
		MemberDef->SetSubPivot({ WinSize.x * 0.325f, WinSize.y * 0.66f });
		break;
	default:
		break;
	}

	return true;
}

void PartyMemWindow::MainUpdate()
{
	CurPlayer = GameSystem::GetBattlememberStatus(Index);
	if (CurPlayer->Level ==0)
	{
		return;
	}
	MemberName->SetString(CurPlayer->Name);
	MakeLvString(GlobalString);
	MemberLevel->SetString(GlobalString.c_str());
	MakeHMPString(GlobalString);
	MemberHP->SetString(GlobalString.c_str());
	MakeHMPString(GlobalString, 1);
	MemberMP->SetString(GlobalString.c_str());
	MakeAtkString(GlobalString);
	MemberAtk->SetString(GlobalString.c_str());
	MakeDefString(GlobalString);
	MemberDef->SetString(GlobalString.c_str());

	if (Index == -1)
	{
		PlaneAtk->SetColor({ 0.0f });
		PlaneDef->SetColor({ 0.0f });
	}
	else
	{
		PlaneAtk->SetColor({ 1.0f });
		PlaneDef->SetColor({ 1.0f });
	}

	if (bFontRender == false)
	{
		MemberName->SetColor(0);
		MemberLevel->SetColor(0);
		MemberHP->SetColor(0);
		MemberMP->SetColor(0);
		MemberAtk->SetColor(0);
		MemberDef->SetColor(0);
		PlaneAtk->SetColor(0.0f);
		PlaneDef->SetColor(0.0f);
	}
}

void PartyMemWindow::DbgUpdate()
{
}