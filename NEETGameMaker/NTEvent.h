#pragma once
#include <NTLogic.h>

class NT2DCollision;
class NTCollisionComponent;
class NTEvent : public NTLogic
{
public:
	enum EVENTTYPE
	{
		ET_ONETIME,
		ET_PERSIST,
		ET_NONE
	};
private:
	Autoptr<NT2DCollision> Location;
	bool(*Event)(void*, void*, void*);

	bool EnterTrigger;
	bool StayTrigger;
	bool ExitTrigger;

	void* Param1;
	void* Param2;
	void* Param3;

	EVENTTYPE Type;
	bool Activated;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;

public:
	void SetEvent(bool(*_Func)(void*, void*, void*), EVENTTYPE _Type = ET_ONETIME)
	{
		Event = _Func;
		Type = _Type;
	}

	void SetLocation(NTRECT _Rect);

	void ActivateEvent(void* _Pointer1, void* _Pointer2, void* _Pointer3)
	{
		Event(_Pointer1, _Pointer2, _Pointer3);
		Activated = true;
	}

	void ActivateEvent()
	{
		Event(Param1, Param2, Param3);
		Activated = true;
	}

	void SetTrigger(bool _Enter, bool _Stay, bool _Exit)
	{
		EnterTrigger = _Enter;
		StayTrigger = _Stay;
		ExitTrigger = _Exit;
	}
	
	void SetParameter(void* _Param1, void* _Param2, void* _Param3)
	{
		Param1 = _Param1;
		Param2 = _Param2;
		Param3 = _Param3;
	}

	bool IsActivated()
	{
		return Activated;
	}

	bool* GetActivePointer() // 나중에 씬에 프렌드 걸어서 포인터 주는거 없애기
	{
		return &Activated;
	}

public:
	void ColEnter(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColStay(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColExit(NTCollisionComponent* _Left, NTCollisionComponent* _Right);

public:
	NTEvent();
	~NTEvent();
};

