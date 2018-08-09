#include "WindowSceneBuilder.h"

#include <NTWindow.h>

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

	Autoptr<NTObject> CharacterMenu = GetScene()->CreateObject(L"CharacterMenu", 100);
	CharacterMenu->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	CharacterMenu->GetTransform()->SetLocalScale(1.0f);
	Autoptr<NTPieceWindow> Window01 = CharacterMenu->AddComponent<NTPieceWindow>(8, 7, 1.0f);
}
