#include "WindowSceneBuilder.h"

#include <NTWindow.h>
#include <NTWinShortCut.h>
#include <NTSpRenderer.h>

#include "GameSystem.h"
#include "NTTextWindow.h"
#include "NTPieceWindow.h"
#include "NTPlayer.h"



WindowSceneBuilder::WindowSceneBuilder()
{
}


WindowSceneBuilder::~WindowSceneBuilder()
{
}

void WindowSceneBuilder::SceneBuild()
{
	Autoptr<NTObject> Camera = GetScene()->CreateObject(L"MainCamera", 0);
	Autoptr<NTCamera> CameraComponent = Camera->AddComponent<NTCamera>();

	CameraComponent->PushRenderLayer(100);

	NTVEC2 WinSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	Autoptr<NTObject> CharacterMenu = GetScene()->CreateObject(L"CharacterMenu", UILayer);
	CharacterMenu->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	CharacterMenu->GetTransform()->SetLocalScale(1.0f);

	Autoptr<NTObject> Window01 = GetScene()->CreateObject(L"Window01", UILayer);
	CharacterMenu->AddChild(Window01);
	Autoptr<NTPieceWindow> ActualWin01 = Window01->AddComponent<NTPieceWindow>(4, 2, 0.48f);
	Window01->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * 0.3375f });
	Autoptr<NTFontRenderer> Name01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Name01->SetColor(255, 255, 255, 255);
	Name01->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.065f, 1.0f });
	Name01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Name01->SetSize(25.0f);
	Name01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Name01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Name01->SetString(GameSystem::GetPlayerStatus(0).Name);

	Autoptr<NTFontRenderer> Level01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Level01->SetColor(255, 255, 255, 255);
	Level01->SetSubPivot({ WinSize.x * 0.258f, WinSize.y * 0.065f, 1.0f });
	Level01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Level01->SetSize(25.0f);
	Level01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Level01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	std::wstring tmp = Level01->GetString();
	tmp = L"Lv    ";
	wchar_t tmpbuf[4];
	_itow_s(GameSystem::GetPlayerStatus(0).Level, tmpbuf, 10);
	if (GameSystem::GetPlayerStatus(0).Level < 10)
	{
		tmp += L"  ";
	}
	tmp += tmpbuf;
	Level01->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlainHP01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainHP01->SetColor(255, 255, 255, 255);
	PlainHP01->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.065f + 30.0f, 1.0f });
	PlainHP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainHP01->SetSize(25.0f);
	PlainHP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainHP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainHP01->SetString(L"HP");

	Autoptr<NTFontRenderer> HP01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	HP01->SetColor(255, 255, 255, 255);
	HP01->SetSubPivot({ WinSize.x * 0.2375f, WinSize.y * 0.065f + 30.0f, 1.0f });
	HP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	HP01->SetSize(25.0f);
	HP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	HP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetPlayerStatus(0).CurHP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetPlayerStatus(0).MaxHP, tmpbuf, 10);
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

	Autoptr<NTFontRenderer> PlainMP01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainMP01->SetColor(255, 255, 255, 255);
	PlainMP01->SetSubPivot({ WinSize.x * 0.075f, WinSize.y * 0.065f + 60.0f, 1.0f });
	PlainMP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainMP01->SetSize(25.0f);
	PlainMP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainMP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainMP01->SetString(L"MP");

	Autoptr<NTFontRenderer> MP01 = Window01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MP01->SetColor(255, 255, 255, 255);
	MP01->SetSubPivot({ WinSize.x * 0.2375f, WinSize.y * 0.065f + 60.0f, 1.0f });
	MP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MP01->SetSize(25.0f);
	MP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetPlayerStatus(0).CurMP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetPlayerStatus(0).MaxMP, tmpbuf, 10);
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
		tmp.insert(0, L"       ");
		break;
	default:
		break;
	}
	MP01->SetString(tmp.c_str());

	Autoptr<NTSpRenderer> Atk01 = Window01->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	Atk01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	Atk01->SetSubPivot({-WinSize.x * 0.135f, -WinSize.y * 0.065f});
	Atk01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTSpRenderer> Def01 = Window01->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	Def01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	Def01->SetSubPivot({ 0.0f, -WinSize.y * 0.065f });
	Def01->SetImageIndex(14);
	Def01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTObject> Window02 = GetScene()->CreateObject(L"Window02", UILayer);
	CharacterMenu->AddChild(Window02);
	Autoptr<NTPieceWindow> ActualWin02 = Window02->AddComponent<NTPieceWindow>(4, 2, 0.48f);
	Window02->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * 0.1125f });

	Autoptr<NTObject> Window03 = GetScene()->CreateObject(L"Window03", UILayer);
	CharacterMenu->AddChild(Window03);
	Autoptr<NTPieceWindow> ActualWin03 = Window03->AddComponent<NTPieceWindow>(4, 2, 0.48f);
	Window03->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.1125f });

	Autoptr<NTObject> Window04 = GetScene()->CreateObject(L"Window04", UILayer);
	CharacterMenu->AddChild(Window04);
	Autoptr<NTPieceWindow> ActualWin04 = Window04->AddComponent<NTPieceWindow>(4, 2, 0.48f);
	Window04->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.3375f });

	Autoptr<NTObject> Window05 = GetScene()->CreateObject(L"Window05", UILayer);
	CharacterMenu->AddChild(Window05);
	Autoptr<NTPieceWindow> ActualWin05 = Window05->AddComponent<NTPieceWindow>(6, 9, 0.5f);
	Window05->GetTransform()->SetLocalPosition({ WinSize.x * 0.18f, 0.0f });
}
