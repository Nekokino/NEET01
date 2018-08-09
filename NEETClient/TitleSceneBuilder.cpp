#include "TitleSceneBuilder.h"
#include "TestPlaneLogic.h"
#include <NTSpRenderer.h>
#include "TestLogic.h"


TitleSceneBuilder::TitleSceneBuilder()
{
}


TitleSceneBuilder::~TitleSceneBuilder()
{
}

void TitleSceneBuilder::SceneBuild()
{
	Autoptr<NTObject> Camera = GetScene()->CreateObject(L"MainCamera", 0);
	Autoptr<NTCamera> CameraComponent = Camera->AddComponent<NTCamera>();
	CameraComponent->PushRenderLayer(0, 1, 2, 3, 4);

	Autoptr<NTObject> PenTest = GetScene()->CreateObject(L"PenRenderer", 0);
	PenTest->AddComponent<TestLogic>();
}
