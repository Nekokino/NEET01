#include "NTNPC.h"
#include <CustomMacro.h>
#include <NTSpRenderer.h>
#include <NT2DCollision.h>
#include <NTSpFrameAnimator.h>
#include <DebugFunc.h>
#include <NTScene.h>
#include "NTPlayer.h"
#include "NTEvent.h"
#include "NTEventSystem.h"
#include "NTTextWindow.h"





#include "DebugSceneUpdater.h"

NTNPC::NTNPC() : Renderer(nullptr), Collider(nullptr), Animator(nullptr), RType(NRT_MAX), EType(NET_MAX), CurListIndex(0), NextEvent(false), EventCount(0)
{
	
}


NTNPC::~NTNPC()
{

}

bool NTNPC::Init(NPCRENDERTYPE _RType, NPCEVENTTYPE _EType)
{
	RType = _RType;
	EType = _EType;
	switch (RType)
	{
	case NRT_AD_GREENGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
		Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
		Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);
#pragma region GreenGuy Create Animation
		Animator->CreateAnimation(L"IdleDown", 110, 110, DFS, false);
		Animator->CreateAnimation(L"WalkDown", 111, 114, DFS, true);
		Animator->CreateAnimation(L"IdleUp", 115, 115, DFS, false);
		Animator->CreateAnimation(L"WalkUp", 116, 119, DFS, true);
		Animator->CreateAnimation(L"IdleLeft", 120, 120, DFS, false);
		Animator->CreateAnimation(L"WalkLeft", 121, 124, DFS, true);
#pragma endregion
		Animator->ChangeAnimation(L"IdleDown");
		break;
	case NRT_AD_BROWNGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
		Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
		Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);
		break;
	case NRT_AD_REDGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
		Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
		Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);
		break;
	case NRT_AD_BLUEGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
		Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
		Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);
		break;
	case NRT_AD_GONZALEZ:
		Renderer = AddComponent<NTSpRenderer>(L"Enemy_Gonz.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
		Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
		Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);
		break;
	case NRT_MAX:
	default:
		tassert(true);
		return false;
		break;
	}

	Autoptr<NTEvent> EventPointer = nullptr;

	switch (EType)
	{
	case NET_CONVERSATION:
		EventPointer = GetNTObject()->AddComponent<NTEvent>();
		EventList.push_back(EventPointer);
		EventPointer->SetEvent(NTEventSystem::FindEvent(L"ConvEvent"));
		break;
	case NET_CONVBATLLE:
		EventPointer = GetNTObject()->AddComponent<NTEvent>();
		EventPointer->SetEvent(NTEventSystem::FindEvent(L"ConvEvent"));
		EventList.push_back(EventPointer);
		EventPointer = GetNTObject()->AddComponent<NTEvent>();
		EventPointer->SetEvent(NTEventSystem::FindEvent(L"BattleEnterEvent"));
		EventList.push_back(EventPointer);
		break;
	case NET_SHOP:
		break;
	case NET_MAX:
	default:
		tassert(true);
		return false;
		break;
	}

	GetNTObject()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	GetNTObject()->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });

	Renderer->SetSubScale({ 400.0f, 400.0f, 1.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	

	return true;
}

void NTNPC::MainUpdate()
{
	if (NextEvent == true)
	{
		if (GameSystem::GetTextWindowStatus() == false)
		{
			std::list<Autoptr<NTEvent>>::iterator EventIter = EventList.begin();
			for (int i = 0; i < EventCount; ++i)
			{
				++EventIter;
			}
			Autoptr<NTObject> Tmp = GetScene()->FindObject(L"BattleSystem", 0);
			(*EventIter)->ActivateEvent(Tmp, GetScene()->GetUpdater<DebugSceneUpdater>()->GetEnemyList(), nullptr);
			
			if (EventList.size() - 1 == EventCount)
			{
				NextEvent = false;
				EventCount = 0;
			}
		}
	}
}

void NTNPC::DbgRender()
{

}

void NTNPC::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	
}


void NTNPC::ColStay(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	// 흠.
	// 여기에 함수를 내맘대로 추가하고 싶다.
	// 그것도 객체별로 따로따로
	// 그럼 함수포인터지
	// 그걸 펑셔널로 바꾸고
	// 근데 또 함수 하나만 하고싶을리가 없지
	// 그럼 펑셔널 리스트고
	// 근데 객체마다 엔터 스테이 엑시트가 있으니까
	// 세개씩 가지고
	// 아이고 맙소사
	// 또 펑셔널들을 총체적으로 관리하고싶으니까
	// 밖에서 얘들을 전부 들고있으면서
	// 파일입출력으로 관리가 되는 툴용 뭔가를 만들고
	// 어ㅏ헣ㅎ허헣
	// 게다가 들어온 콜리전 컴포넌트 종류에 따라서 다르고 엏ㅎ허

	const wchar_t* ColliderName = _Right->GetName();
	
	if (0 == lstrcmpW(ColliderName, L"MainCollider"))
	{
#pragma region RectRangeCol
		NTVEC LeftColliderVec = Collider->GetIndVec();
		NTVEC RightColliderVec = _Right->GetNTObject()->GetComponent<NT2DCollision>()->GetIndVec();

		NTVEC LeftWorldPos = GetNTObject()->GetTransform()->GetLocalPosition();
		NTVEC RightWorldPos = _Right->GetNTObject()->GetTransform()->GetLocalPosition();

		float Degree = MathSystem::GetDegree2D(LeftWorldPos, RightWorldPos);

		if (Degree >= 315.0f || Degree <= 45.0f)
		{
			_Right->GetNTObject()->GetTransform()->SetLocalMove({ (LeftWorldPos.x + LeftColliderVec.Right()) - (RightWorldPos.x + RightColliderVec.Left()), 0.0f });
		}

		if (Degree >= 45.0f && Degree <= 135.0f)
		{
			_Right->GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, (LeftWorldPos.y + LeftColliderVec.Top()) - (RightWorldPos.y + RightColliderVec.Bottom()) + 0.5f });
		}

		if (Degree >= 135.0f && Degree <= 225.0f)
		{
			_Right->GetNTObject()->GetTransform()->SetLocalMove({ (LeftWorldPos.x + LeftColliderVec.Left()) - (RightWorldPos.x + RightColliderVec.Right()) - 0.5f, 0.0f });
		}

		if (Degree >= 225.0f && Degree <= 315.0f)
		{
			_Right->GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, (LeftWorldPos.y + LeftColliderVec.Bottom()) - (RightWorldPos.y + RightColliderVec.Top()) - 0.5f });
		}
#pragma endregion
	}

	if (0 == lstrcmpW(ColliderName, L"EventCollider"))
	{
		if (EType == NET_CONVBATLLE || EType == NET_CONVERSATION)
		{
			ActiveTextEvent();
		}
	}
}

void NTNPC::ActiveTextEvent()
{
	if (TextIndex.size() != 0)
	{
		int Color = 0xffffff0f;
		wchar_t tmp[TextMaxBuf] = {};
		lstrcpyW(tmp, GameSystem::GetText(TextIndex[CurListIndex][CurTextCount]));
		swprintf_s(tmp, TextMaxBuf, tmp, GetName());
		std::list<Autoptr<NTEvent>>::iterator EventIter = EventList.begin();
		(*EventIter)->ActivateEvent(tmp, &Color, nullptr);
		++CurTextCount;
		if (TextIndex[CurListIndex].size() > (size_t)CurTextCount)
		{
			GameSystem::SetNextText(this, true);
		}
		else
		{
			CurTextCount = 0;
			GameSystem::ClearNPC();
			if (EType == NET_CONVBATLLE)
			{
				GetScene()->GetUpdater<DebugSceneUpdater>()->AddEnemyList(GetNTObject());
			}
			if (EventList.size() > (size_t)EventCount + 1)
			{
				NextEvent = true;
				++EventCount;
			}
		}
	}
}