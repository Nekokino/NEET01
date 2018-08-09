#include "NTEvent.h"
#include "GameSystem.h"
#include <DebugFunc.h>
#include <NT2DCollision.h>

NTEvent::NTEvent() : Location(nullptr), Event(nullptr), EnterTrigger(nullptr), StayTrigger(nullptr), ExitTrigger(nullptr), Param1(nullptr), Param2(nullptr), Param3(nullptr), Type(ET_NONE), Activated(false)
{
}


NTEvent::~NTEvent()
{
}

bool NTEvent::Init()
{
	Location = AddComponent<NT2DCollision>(EventLayer);
	Location->SetMode(COLTYPE::CT_2D_RECT);

	Location->EnterFunc<NTEvent>(this, &NTEvent::ColEnter);
	Location->StayFunc<NTEvent>(this, &NTEvent::ColStay);
	Location->ExitFunc<NTEvent>(this, &NTEvent::ColExit);
	return true;
}

void NTEvent::MainUpdate()
{
	if (Type == ET_PERSIST) // 선행조건도 이벤트로 넣는다면 함수포인터의 리스트를 만들어서 모두 true일때 실행되게. 어차피 순회해야함
	{
		ActivateEvent();
		Activated = true;
	}
}

void NTEvent::DbgRender()
{
	DebugFunc::DrawRect(Location->GetRect());
}

void NTEvent::SetLocation(NTRECT _Rect)
{
	Location->SetRect(_Rect);
}

void NTEvent::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	if (EnterTrigger == false)
	{
		return;
	}

	Event(Param1, Param2, Param3);
	Activated = true;
}

void NTEvent::ColStay(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	if (StayTrigger == false)
	{
		return;
	}

	Event(Param1, Param2, Param3);
	Activated = true;
}

void NTEvent::ColExit(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	if (ExitTrigger == false)
	{
		return;
	}

	Event(Param1, Param2, Param3);
	Activated = true;
}