#include "TestSceneUpdater.h"
#include <NTWindow.h>
#include <InputSystem.h>
#include <TimeSystem.h>
#include <NTObject.h>
#include <NTSpRenderer.h>
#include <NTTextWindow.h>
#include <NTWinShortCut.h>
#include <DebugFunc.h>
#include <NTFadeRect.h>


TestSceneUpdater::TestSceneUpdater() : UIObj(nullptr), UICamera(nullptr), TextWindow(nullptr), MousePos({ 0, 0 })
{
	
}


TestSceneUpdater::~TestSceneUpdater()
{
}


wchar_t TmpString[256] = {};

void TestSceneUpdater::SceneUpdate()
{
	
}

void TestSceneUpdater::SceneStart()
{
	UICamera = GetScene()->CreateObject(L"UICam", 0);
	Autoptr<NTCamera> CameraCom = UICamera->AddComponent<NTCamera>();

	CameraCom->PushRenderLayer(100);

	UIObj = GetScene()->CreateObject(L"UIObj", 100);
	UIObj->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	UIObj->GetTransform()->SetLocalScale(1.0f);
	TextWindow = UIObj->AddComponent<NTTextWindow>(L"TextWindow.png", 100);

	FontRender = UIObj->AddComponent<NTFontRenderer>(L"±Ã¼­");
	FontRender->SetColor(255, 125, 122, 255);
	FontRender->SetSubPivot({ 0.0f, 0.0f, 1.0f });
	FontRender->SetSubScale({ 1.0f, 1.0f, 1.0f });
	FontRender->SetSize(50.0f);
	FontRender->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	FontRender->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	FadeRect = UIObj->AddComponent<NTFadeRect>();
	
}