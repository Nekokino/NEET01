#include "PartyMemWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTSpRenderer.h>
#include <NTFontRenderer.h>
#include <NTWinShortCut.h>


#define FirstPos { WinSize.x * -0.27f, WinSize.y * 0.3375f }
#define SecondPos { WinSize.x * -0.27f, WinSize.y * 0.1125f }
#define ThirdPos { WinSize.x * -0.27f, WinSize.y * -0.1125f }

PartyMemWindow::PartyMemWindow()
{
}


PartyMemWindow::~PartyMemWindow()
{
}

bool PartyMemWindow::Init(int _Index)
{
	if (_Index >= 3)
	{
		return false;
	}

	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	WindowRenderer = GetNTObject()->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	GetNTObject()->GetTransform()->SetLocalPosition(FirstPos);

	Autoptr<NTFontRenderer> Name01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Name01->SetColor(255, 255, 255, 255);
	Name01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f, 1.0f });
	Name01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Name01->SetSize(25.0f);
	Name01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Name01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Name01->SetString(GameSystem::GetBattlememberStatus(0).Name);

	Autoptr<NTFontRenderer> Level01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Level01->SetColor(255, 255, 255, 255);
	Level01->SetSubPivot({ WinSize.x * 0.275f, WinSize.y * 0.065f, 1.0f });
	Level01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Level01->SetSize(25.0f);
	Level01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Level01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	std::wstring tmp = Level01->GetString();
	tmp = L"Lv    ";
	wchar_t tmpbuf[32];
	_itow_s(GameSystem::GetBattlememberStatus(0).Level, tmpbuf, 10);
	if (GameSystem::GetBattlememberStatus(0).Level < 10)
	{
		tmp += L"  ";
	}
	tmp += tmpbuf;
	Level01->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlainHP01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainHP01->SetColor(255, 255, 255, 255);
	PlainHP01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 30.0f, 1.0f });
	PlainHP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainHP01->SetSize(25.0f);
	PlainHP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainHP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainHP01->SetString(L"HP");

	Autoptr<NTFontRenderer> HP01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	HP01->SetColor(255, 255, 255, 255);
	HP01->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 30.0f, 1.0f });
	HP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	HP01->SetSize(25.0f);
	HP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	HP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).CurHP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetBattlememberStatus(0).MaxHP, tmpbuf, 10);
	tmp += tmpbuf;
	int tmpint = 11 - lstrlenW(tmp.c_str());
	switch (tmpint)
	{
	case 3:
		tmp.insert(0, L"  ");
		break;
	case 4:
		tmp.insert(0, L"   ");
		break;
	case 5:
		tmp.insert(0, L"     ");
		break;
	case 6:
		tmp.insert(0, L"       ");
		break;
	default:
		break;
	}
	HP01->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlainMP01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainMP01->SetColor(255, 255, 255, 255);
	PlainMP01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 60.0f, 1.0f });
	PlainMP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainMP01->SetSize(25.0f);
	PlainMP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainMP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainMP01->SetString(L"MP");

	Autoptr<NTFontRenderer> MP01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MP01->SetColor(255, 255, 255, 255);
	MP01->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 60.0f, 1.0f });
	MP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MP01->SetSize(25.0f);
	MP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).CurMP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetBattlememberStatus(0).MaxMP, tmpbuf, 10);
	tmp += tmpbuf;
	tmpint = 11 - lstrlenW(tmp.c_str());
	switch (tmpint)
	{
	case 3:
		tmp.insert(0, L"  ");
		break;
	case 4:
		tmp.insert(0, L"   ");
		break;
	case 5:
		tmp.insert(0, L"     ");
		break;
	case 6:
		tmp.insert(0, L"      ");
		break;
	default:
		break;
	}
	MP01->SetString(tmp.c_str());

	Autoptr<NTSpRenderer> PlaneAtk01 = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneAtk01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneAtk01->SetSubPivot({ -WinSize.x * 0.115f, -WinSize.y * 0.065f });
	PlaneAtk01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> Atk01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Atk01->SetColor(255, 255, 255, 255);
	Atk01->SetSubPivot({ WinSize.x * 0.175f, WinSize.y * 0.21f });
	Atk01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Atk01->SetSize(25.0f);
	Atk01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Atk01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	int Damage = GameSystem::GetBattlememberStatus(0).Power + GameSystem::GetBattlememberStatus(0).Weapon.Atk;
	_itow_s(Damage, tmpbuf, 10);
	tmp += tmpbuf;
	Atk01->SetString(tmp.c_str());

	Autoptr<NTSpRenderer> PlaneDef01 = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneDef01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneDef01->SetSubPivot({ WinSize.x * 0.025f, -WinSize.y * 0.065f });
	PlaneDef01->SetImageIndex(14);
	PlaneDef01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> Def01 = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Def01->SetColor(255, 255, 255, 255);
	Def01->SetSubPivot({ WinSize.x * 0.325f, WinSize.y * 0.21f });
	Def01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Def01->SetSize(25.0f);
	Def01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Def01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	int Defence = GameSystem::GetBattlememberStatus(0).Stamina + GameSystem::GetBattlememberStatus(0).Armor.Def + GameSystem::GetBattlememberStatus(0).Helmet.Def;
	_itow_s(Defence, tmpbuf, 10);
	tmp += tmpbuf;
	Def01->SetString(tmp.c_str());
}

void PartyMemWindow::MainUpdate()
{
}

void PartyMemWindow::DbgUpdate()
{
}