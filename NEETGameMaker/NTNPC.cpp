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

NTNPC::NTNPC() : Renderer(nullptr), Collider(nullptr), Animator(nullptr), Event(nullptr), RType(NRT_MAX), EType(NET_MAX), CurTextCount(0)
{
	
}


NTNPC::~NTNPC()
{

}

bool NTNPC::Init(NPCRENDERTYPE _RType, NPCEVENTTYPE _EType)
{
	Event = AddComponent<NTEvent>();

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
		break;
	case NRT_AD_REDGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		break;
	case NRT_AD_BLUEGUY:
		Renderer = AddComponent<NTSpRenderer>(L"NPC_AD1_Com.png");
		Collider = AddComponent<NT2DCollision>(NPCLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
		break;
	case NRT_MAX:
	default:
		tassert(true);
		return false;
		break;
	}
	switch (EType)
	{
	case NET_CONVERSATION:
		Event->SetEvent(NTEventSystem::FindEvent(L"ConvEvent"));
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

	Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
	Collider->EnterFunc<NTNPC>(this, &NTNPC::ColEnter);
	Collider->StayFunc<NTNPC>(this, &NTNPC::ColStay);

	return true;
}

void NTNPC::MainUpdate()
{
	
}

void NTNPC::DbgRender()
{

}

void NTNPC::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	
}


void NTNPC::ColStay(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	// ��.
	// ���⿡ �Լ��� ������� �߰��ϰ� �ʹ�.
	// �װ͵� ��ü���� ���ε���
	// �׷� �Լ���������
	// �װ� ��ųη� �ٲٰ�
	// �ٵ� �� �Լ� �ϳ��� �ϰ�������� ����
	// �׷� ��ų� ����Ʈ��
	// �ٵ� ��ü���� ���� ������ ����Ʈ�� �����ϱ�
	// ������ ������
	// ���̰� ���һ�
	// �� ��ųε��� ��ü������ �����ϰ�����ϱ�
	// �ۿ��� ����� ���� ��������鼭
	// ������������� ������ �Ǵ� ���� ������ �����
	// ��S�����S
	// �Դٰ� ���� �ݸ��� ������Ʈ ������ ���� �ٸ��� �j����

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
		ActiveTextEvent();
	}
}

void NTNPC::ActiveTextEvent()
{
	if (TextIndex.size() != 0)
	{
		int Color = 0xffffff0f;
		wchar_t* tmp = GameSystem::GetText(TextIndex[CurTextCount]);
		swprintf_s(tmp, lstrlenW(tmp) + lstrlenW(GetName()), tmp, GetName());
		Event->ActivateEvent(tmp, &Color, nullptr);
		++CurTextCount;
		if (TextIndex.size() > CurTextCount)
		{
			GameSystem::SetNextText(this, true);
		}
		else
		{
			CurTextCount = 0;
			GameSystem::ClearNPC();
		}
	}
}