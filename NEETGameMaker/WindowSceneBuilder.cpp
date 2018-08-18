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

	CameraComponent->PushRenderLayer(100);

	NTVEC2 WinSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	Autoptr<NTObject> CharacterMenu = GetScene()->CreateObject(L"CharacterMenu", UILayer);
	CharacterMenu->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	CharacterMenu->GetTransform()->SetLocalScale(1.0f);

	Autoptr<PartyWindow> PartyWindow = CharacterMenu->AddComponent<class PartyWindow>();

}
