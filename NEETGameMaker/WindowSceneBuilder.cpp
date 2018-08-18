#include "WindowSceneBuilder.h"

#include <NTWindow.h>
#include <NTWinShortCut.h>
#include <NTSpRenderer.h>

#include "GameSystem.h"
#include "NTTextWindow.h"
#include "NTPieceWindow.h"
#include "NTPlayer.h"
#include "PartyWindow.h"



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

	CameraComponent->PushRenderLayer(UILayer);

	NTVEC2 WinSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	Autoptr<NTObject> CharacterMenu = GetScene()->CreateObject(L"CharacterMenu", UILayer);
	CharacterMenu->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	CharacterMenu->GetTransform()->SetLocalScale(1.0f);

	Autoptr<PartyWindow> PartyWindow = CharacterMenu->AddComponent<class PartyWindow>();

	Autoptr<NTObject> Background = GetScene()->CreateObject(L"Background", UILayer);
	Background->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 9.0f });
	Background->GetTransform()->SetLocalScale(1.0f);

	for (size_t i = 0; i < 10; i++)
	{
		Autoptr<NTSpRenderer> BG = Background->AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
		BG->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		BG->SetImageIndex(35);
		BG->SetSubScale({ WinSize.x * 0.155f, WinSize.y * 0.1f, 1.0f });
		BG->SetSubPivot({ WinSize.x * -0.5f + WinSize.x * 0.155f * i, WinSize.y * 0.5f });
	}

	for (size_t i = 0; i < 10; i++)
	{
		Autoptr<NTSpRenderer> BG = Background->AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
		BG->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		BG->SetImageIndex(35);
		BG->SetSubScale({ WinSize.x * 0.155f, WinSize.y * 0.1f, 1.0f });
		BG->SetSubPivot({ WinSize.x * -0.5f , WinSize.y * 0.5f - WinSize.y * 0.1f * i });
	}

	for (size_t i = 0; i < 10; i++)
	{
		Autoptr<NTSpRenderer> BG = Background->AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
		BG->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		BG->SetImageIndex(35);
		BG->SetSubScale({ WinSize.x * 0.155f, WinSize.y * 0.1f, 1.0f });
		BG->SetSubPivot({ WinSize.x * -0.5f + WinSize.x * 0.155f * i, WinSize.y * -0.5f });
	}

	for (size_t i = 0; i < 10; i++)
	{
		Autoptr<NTSpRenderer> BG = Background->AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
		BG->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		BG->SetImageIndex(35);
		BG->SetSubScale({ WinSize.x * 0.155f, WinSize.y * 0.1f, 1.0f });
		BG->SetSubPivot({ WinSize.x * 0.495f , WinSize.y * 0.5f - WinSize.y * 0.1f * i });
	}

}
