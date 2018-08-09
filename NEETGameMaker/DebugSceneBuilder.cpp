#include "DebugSceneBuilder.h"

#include "NTEventSystem.h"
#include "GameSystem.h"
#include "NTPlayer.h"
#include "NTField.h"
#include "FieldCamera.h"
#include "NTEvent.h"
#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>
#include "EnableRange.h"
#include "NTNPC.h"
#include "NTFadeRect.h"
#include "NTTextWindow.h"
#include "NTPixelChecker.h"
#include "NTPixelCollider.h"


DebugSceneBuilder::DebugSceneBuilder()
{
}


DebugSceneBuilder::~DebugSceneBuilder()
{
}

void DebugSceneBuilder::SceneBuild()
{
	NTEventSystem::Init();

	GetScene()->_2DCollsionSystem.Link(NPCLayer, PlayerLayer);
	GetScene()->_2DCollsionSystem.Link(NPCLayer, EventLayer);
	GetScene()->_2DCollsionSystem.Link(EventLayer, PlayerLayer);

	Autoptr<NTObject> Camera = GetScene()->CreateObject(L"MainCamera", 0);
	Autoptr<NTCamera> CameraComponent = Camera->AddComponent<NTCamera>();



	CameraComponent->PushRenderLayer(0, 1, 2, 3, 4, 10);

	Autoptr<NTObject> TestPlane = GetScene()->CreateObject(L"TPlane", 0);
	Autoptr<NTPlayer> P_Kaeru = TestPlane->AddComponent<NTPlayer>(GameSystem::CHARACTER::KAERU);
	

	Autoptr<NTObject> Field = GetScene()->CreateObject(L"MainField", 0);
	Autoptr<NTField> Test11 = Field->AddComponent<NTField>();
	Test11->ChangeField(L"Leene_Center");
	P_Kaeru->SetFieldRenderer(Test11->GetColImage());
	Autoptr<FieldCamera> CamLogic = Camera->AddComponent<FieldCamera>(CameraComponent, TestPlane->GetTransform(), Test11);
	Autoptr<NTEvent> MoveMapEvent1 = Field->AddComponent<NTEvent>();
	MoveMapEvent1->SetEvent(NTEventSystem::FindEvent(L"FadeOutEvent"));
	MoveMapEvent1->SetLocation({ 1530.0f, 1260.0f, 10.0f, 40.0f });
	MoveMapEvent1->SetParameter(nullptr, nullptr, nullptr);
	MoveMapEvent1->SetTrigger(true, false, false);
	Autoptr<NTPixelCollider> PCol = TestPlane->AddComponent<NTPixelCollider>();
	PCol->SetSourceRenderer(Test11->GetColImage());

	Autoptr<NTEvent> RelayEvent1 = Field->AddComponent<NTEvent>();
	RelayEvent1->SetEvent(NTEventSystem::FindEvent(L"MapChangeRelayEvent"), NTEvent::EVENTTYPE::ET_PERSIST);

	Autoptr<NTEvent> FadeInEvent = Field->AddComponent<NTEvent>();
	FadeInEvent->SetEvent(NTEventSystem::FindEvent(L"FadeInEvent"));
	FadeInEvent->SetParameter(nullptr, nullptr, nullptr);

	Autoptr<NTEvent> MainMoveEvent1 = Field->AddComponent<NTEvent>();
	MainMoveEvent1->SetEvent(NTEventSystem::FindEvent(L"MoveMapEvent"));
	MainMoveEvent1->SetParameter(L"Leene_Right", (void*)&NTVEC::FORWARD, FadeInEvent);
	Autoptr<EnableRange> EnRange = P_Kaeru->AddComponent<EnableRange>(Test11);

	Autoptr<NTObject> TestNPC = GetScene()->CreateObject(L"TestNPC", 0);
	Autoptr<NTNPC> NPCLogic = TestNPC->AddComponent<NTNPC>(NTNPC::NPCRENDERTYPE::NRT_AD_GREENGUY, NTNPC::NPCEVENTTYPE::NET_CONVERSATION);
	NPCLogic->AddText(0);
	NPCLogic->AddText(1);
	NPCLogic->SetName(L"À×¾î");

	Test11->AddNPC(TestNPC);

	Autoptr<NTObject> UICamera = GetScene()->CreateObject(L"UICam", 0);
	Autoptr<NTCamera> CameraCom = UICamera->AddComponent<NTCamera>();

	CameraCom->PushRenderLayer(100);

	Autoptr<NTObject> UIObj = GetScene()->CreateObject(L"UIObj", 100);
	UIObj->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	UIObj->GetTransform()->SetLocalScale(1.0f);
	Autoptr<NTTextWindow> TextWindow = UIObj->AddComponent<NTTextWindow>(L"TextWindow.png", 100);

	Autoptr<NTFontRenderer> FontRender = UIObj->AddComponent<NTFontRenderer>(L"±Ã¼­");
	FontRender->SetColor(255, 125, 122, 255);
	FontRender->SetSubPivot({ 0.0f, 0.0f, 1.0f });
	FontRender->SetSubScale({ 1.0f, 1.0f, 1.0f });
	FontRender->SetSize(50.0f);
	FontRender->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	FontRender->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Autoptr<NTFadeRect> FadeRect = UIObj->AddComponent<NTFadeRect>();

	RelayEvent1->SetParameter(MoveMapEvent1->GetActivePointer(), FadeRect->GetCurAlphaPointer(), MainMoveEvent1);
}
