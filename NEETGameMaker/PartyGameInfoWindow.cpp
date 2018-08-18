#include "PartyGameInfoWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTFontRenderer.h>
#include <NTWinShortCut.h>



PartyGameInfoWindow::PartyGameInfoWindow()
{
}


PartyGameInfoWindow::~PartyGameInfoWindow()
{
}

bool PartyGameInfoWindow::Init()
{
	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	Autoptr<NTPieceWindow> ActualWin04 = GetNTObject()->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.3375f });

	Autoptr<NTFontRenderer> PlanePlayTime = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlanePlayTime->SetColor(255, 255, 255, 255);
	PlanePlayTime->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.775f });
	PlanePlayTime->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlanePlayTime->SetSize(25.0f);
	PlanePlayTime->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlanePlayTime->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlanePlayTime->SetString(L"PlayTime");

	PlayTime = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlayTime->SetColor(255, 255, 255, 255);
	PlayTime->SetSubPivot({ WinSize.x * 0.235f, WinSize.y * 0.775f });
	PlayTime->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlayTime->SetSize(25.0f);
	PlayTime->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlayTime->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneGold = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneGold->SetColor(255, 255, 255, 255);
	PlaneGold->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.85f });
	PlaneGold->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneGold->SetSize(25.0f);
	PlaneGold->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneGold->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneGold->SetString(L"Gold");

	Gold = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Gold->SetColor(255, 255, 255, 255);
	Gold->SetSubPivot({ WinSize.x * 0.235f, WinSize.y * 0.85f });
	Gold->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Gold->SetSize(25.0f);
	Gold->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Gold->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	return true;
}

void PartyGameInfoWindow::MainUpdate()
{
	std::wstring TmpStr;
	wchar_t TmpBuf[32];


	int Hour = 0;
	int Min = 0;
	int Time = (int)GameSystem::GetPlayTime();
	Min = Time / 60;
	if (Min >= 60)
	{
		Hour = Min / 60;
		Min %= 60;
	}
	TmpStr.clear();
	swprintf_s(TmpBuf, L"%d : %d", Hour, Min);
	TmpStr += TmpBuf;
	PlayTime->SetString(TmpStr.c_str());

	TmpStr.clear();
	swprintf_s(TmpBuf, L"%d", GameSystem::GetGold());
	TmpStr += TmpBuf;
	Gold->SetString(TmpStr.c_str());
}

void PartyGameInfoWindow::DbgUpdate()
{
}