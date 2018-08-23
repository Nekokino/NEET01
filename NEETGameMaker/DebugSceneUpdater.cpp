#include "DebugSceneUpdater.h"

#include <NTWinShortCut.h>
#include <InputSystem.h>
#include <NTFontRenderer.h>
#include <NTColorMeshRenderer.h>

#include "NTFadeRect.h"
#include "GameSystem.h"
#include "NTPixelChecker.h"

DebugSceneUpdater::DebugSceneUpdater() : Player(nullptr), FontRender(nullptr), FadeRect(nullptr), PixelChecker(nullptr), MousePos({ 0, 0 })
{
	//memset(TextString, 0, sizeof(TextString));
}


DebugSceneUpdater::~DebugSceneUpdater()
{
}

void DebugSceneUpdater::SceneUpdate()
{
	MousePos = { 0,0 };
	GetCursorPos(&MousePos);
	ScreenToClient(NTWinShortCut::GetMainWindow().GetHWND(), &MousePos);

	NTVEC MPos = {};

	MPos.x = (float)MousePos.x;
	MPos.y = (float)-MousePos.y;

	float tmasdf = NTWinShortCut::GetMainWindow().GetHeightf() * 0.5f;

	MPos.x -= (NTWinShortCut::GetMainWindow().GetWidthf() * 0.5f);
	MPos.y += (NTWinShortCut::GetMainWindow().GetHeightf() * 0.5f);
	

	NTVEC CamPos = NTWinShortCut::GetMainSceneSystem().GetCurScene()->GetMainCamera()->GetNTObject()->GetTransform()->GetWorldPosition();
	
	MPos.x += CamPos.x;
	MPos.y += CamPos.y;

	//swprintf_s(TextString, 256, L"%f, %f", MPos.x, MPos.y);
	//if (TextString != nullptr)
	//{
	//	FontRender->SetString(TextString);
	//}

	/*swprintf_s(TextString, 256, L"%f, %f", Player->GetTransform()->GetLocalPosition().x, Player->GetTransform()->GetLocalPosition().y);
	if (TextString != nullptr)
	{
		FontRender->SetString(TextString);
	}*/

	
	//swprintf_s(TextString, 256, L"%f", TimeSystem::FPS());
	//if (TextString != nullptr)
	//{
	//	FontRender->SetString(TextString);
	//}

	//NTCOLOR Color = PixelChecker->GetPixelColor(MPos.x, MPos.y);
	//swprintf_s(TextString, 256, L"%f, %f, %f, %f", Color.r, Color.g, Color.b, Color.a);
	//if (TextString != nullptr)
	//{
	//	FontRender->SetString(TextString);
	//}
}

void DebugSceneUpdater::SceneStart()
{
	Autoptr<NTObject> UI = GetScene()->FindObject(L"UIObj", UILayer);
	FontRender = UI->GetComponent<NTFontRenderer>(1);
	FadeRect = UI->GetComponent<NTFadeRect>();
	Player = GetScene()->FindObject(L"Player01", PlayerLayer);
	PixelChecker = Player->GetComponent<NTPixelChecker>();
	
}
