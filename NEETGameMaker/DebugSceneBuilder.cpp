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
#include "BattleSystem.h"
#include "NTBattle.h"


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

	Autoptr<NTObject> BattleSystemObj = GetScene()->CreateObject(L"BattleSystem", 0);
	Autoptr<BattleSystem> BattleSystemCom = BattleSystemObj->AddComponent<BattleSystem>();

	CameraComponent->PushRenderLayer(0, 1, 2, 3, 4, 10);

	Autoptr<NTObject> TestPlane = GetScene()->CreateObject(L"Player01", 0);
	Autoptr<NTPlayer> P_Kaeru = TestPlane->AddComponent<NTPlayer>(CHARACTER::KAERU);
	P_Kaeru->SetFront();

	Autoptr<NTObject> TestPlane2 = GetScene()->CreateObject(L"Player02", 0);
	Autoptr<NTPlayer> P_TEST = TestPlane2->AddComponent<NTPlayer>(CHARACTER::CHRONO);

	Autoptr<NTObject> TestPlane3 = GetScene()->CreateObject(L"Player03", 0);
	Autoptr<NTPlayer> P_TEST2  = TestPlane3->AddComponent<NTPlayer>(CHARACTER::MARU);

	Autoptr<NTObject> Field = GetScene()->CreateObject(L"MainField", 0);
	Autoptr<NTField> Test11 = Field->AddComponent<NTField>();
	Test11->ChangeField(L"Leene_Center");
	P_Kaeru->SetFieldRenderer(Test11->GetColImage());
	P_TEST->SetFieldRenderer(Test11->GetColImage());
	P_TEST2->SetFieldRenderer(Test11->GetColImage());
	Autoptr<FieldCamera> CamLogic = Camera->AddComponent<FieldCamera>(CameraComponent, TestPlane->GetTransform(), Test11);

	Autoptr<NTEvent> FadeInEvent = Field->AddComponent<NTEvent>();
	FadeInEvent->SetEvent(NTEventSystem::FindEvent(L"FadeInEvent"));
	FadeInEvent->SetParameter(nullptr, nullptr, nullptr);

	Autoptr<NTEvent> MoveMapEvent1 = Field->AddComponent<NTEvent>(); // 굳이 필드일 필요 없음.
	MoveMapEvent1->SetEvent(NTEventSystem::FindEvent(L"FadeOutEvent"));
	MoveMapEvent1->SetLocation({ 1530.0f, 1260.0f, 10.0f, 40.0f });
	MoveMapEvent1->SetParameter(nullptr, nullptr, nullptr);
	MoveMapEvent1->SetTrigger(true, false, false);

	Autoptr<NTEvent> RelayEvent1 = Field->AddComponent<NTEvent>();
	RelayEvent1->SetEvent(NTEventSystem::FindEvent(L"MapChangeRelayEvent"), NTEvent::EVENTTYPE::ET_PERSIST);

	Autoptr<NTEvent> MainMoveEvent1 = Field->AddComponent<NTEvent>();
	MainMoveEvent1->SetEvent(NTEventSystem::FindEvent(L"MoveMapEvent"));
	MainMoveEvent1->SetParameter(L"Leene_Right", (void*)&NTVEC::FORWARD, FadeInEvent);

	Autoptr<EnableRange> EnRange = P_Kaeru->AddComponent<EnableRange>(Test11);

	Autoptr<NTEvent> MoveMapEvent2 = Field->AddComponent<NTEvent>();
	MoveMapEvent2->SetEvent(NTEventSystem::FindEvent(L"FadeOutEvent"));
	MoveMapEvent2->SetLocation({ -1530.0f, 1080.0f, 10.0f, 40.0f });
	MoveMapEvent2->SetParameter(nullptr, nullptr, nullptr);
	MoveMapEvent2->SetTrigger(true, false, false);

	Autoptr<NTEvent> RelayEvent2 = Field->AddComponent<NTEvent>();
	RelayEvent2->SetEvent(NTEventSystem::FindEvent(L"MapChangeRelayEvent"), NTEvent::EVENTTYPE::ET_PERSIST);

	Autoptr<NTEvent> MainMoveEvent2 = Field->AddComponent<NTEvent>();
	MainMoveEvent2->SetEvent(NTEventSystem::FindEvent(L"MoveMapEvent"));
	MainMoveEvent2->SetParameter(L"Leene_Left", (void*)&NTVEC::FORWARD, FadeInEvent);

	Autoptr<NTObject> UICamera = GetScene()->CreateObject(L"UICam", 0);
	Autoptr<NTCamera> CameraCom = UICamera->AddComponent<NTCamera>();

	CameraCom->PushRenderLayer(100);

	Autoptr<NTObject> UIObj = GetScene()->CreateObject(L"UIObj", 100);
	UIObj->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	UIObj->GetTransform()->SetLocalScale(1.0f);
	Autoptr<NTTextWindow> TextWindow = UIObj->AddComponent<NTTextWindow>(L"TextWindow.png", 100);

	Autoptr<NTFontRenderer> FontRender = UIObj->AddComponent<NTFontRenderer>(L"궁서");
	FontRender->SetColor(255, 125, 122, 255);
	FontRender->SetSubPivot({ 0.0f, 0.0f, 1.0f });
	FontRender->SetSubScale({ 1.0f, 1.0f, 1.0f });
	FontRender->SetSize(50.0f);
	FontRender->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	FontRender->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Autoptr<NTFadeRect> FadeRect = UIObj->AddComponent<NTFadeRect>();

	RelayEvent1->SetParameter(MoveMapEvent1->GetActivePointer(), FadeRect->GetCurAlphaPointer(), MainMoveEvent1);
	RelayEvent2->SetParameter(MoveMapEvent2->GetActivePointer(), FadeRect->GetCurAlphaPointer(), MainMoveEvent2);
}
