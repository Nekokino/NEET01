#include "NTEventSystem.h"
#include <NTWinShortCut.h>
#include <NTSpRenderer.h>
#include "NTTextWindow.h"
#include "NTField.h"
#include "GameSystem.h"
#include "NTFadeRect.h"
#include "NTEvent.h"

std::unordered_map<std::wstring, bool(*)(void*, void*, void*)> NTEventSystem::EventMap;

void NTEventSystem::Init()
{
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"TestEvent", &NTEventSystem::TestEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"ConvEvent", &NTEventSystem::ConversationEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"MoveMapEvent", &NTEventSystem::MoveMapEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"FadeOutEvent", &NTEventSystem::FadeOutEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"MapChangeRelayEvent", &NTEventSystem::MapChangeRelayEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"FadeInEvent", &NTEventSystem::FadeInEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"IsEqualEvent", &NTEventSystem::IsEqualEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"IsBiggerIntEvent", &NTEventSystem::IsBiggerIntEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"IsSmallerIntEvent", &NTEventSystem::IsSmallerIntEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"IsBiggerFloatEvent", &NTEventSystem::IsBiggerFloatEvent));
	EventMap.insert(std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::value_type(L"IsSmallerFloatEvent", &NTEventSystem::IsSmallerFloatEvent));
}

bool NTEventSystem::ConversationEvent(void * _String, void* _Color, void* _Unuse)
{
	if (_String == nullptr)
	{
		return false;
	}

	Autoptr<NTTextWindow> TW = NTWinShortCut::GetMainSceneSystem().GetCurScene()->RenderSystem.GetRenderer(L"TextWindow.png", 100)->GetNTObject()->GetComponent<NTTextWindow>();

	TW->OpenText();
	TW->SetString((const wchar_t*)_String);
	if (_Color == nullptr)
	{
		TW->SetColor(0, 255, 255, 255);
	}
	else
	{
		int Color = *(int*)_Color;

		TW->SetColor(Color);
	}
	

	return true;
}

bool NTEventSystem::MoveMapEvent(void * _MapName, void * _Position, void* _NextEvent)
{
	if (_MapName == nullptr || _Position == nullptr || _NextEvent == nullptr)
	{
		return false;
	}
	Autoptr<NTEvent> Event = (NTEvent*)_NextEvent;

	Autoptr<NTField> Field = NTWinShortCut::GetMainSceneSystem().GetCurScene()->FindObject(L"MainField", 0)->GetComponent<NTField>();
	Field->ChangeField((const wchar_t*)_MapName);
	Autoptr<NTObject> Player = NTWinShortCut::GetMainSceneSystem().GetCurScene()->FindObject(L"TPlane", 0);
	NTVEC Pos = *(NTVEC*)_Position;
	Player->GetTransform()->SetLocalPosition(Pos);
	Event->ActivateEvent();
	return true;
}

bool NTEventSystem::FadeOutEvent(void * _Speed, void * _Unuse1, void* _Unuse2)
{
	float Speed = 0.0f;
	if (_Speed != nullptr)
	{
		Speed = *(float*)_Speed;
	}
	else
		Speed = 1.0f;

	Autoptr<NTObject> UI = NTWinShortCut::GetMainSceneSystem().GetCurScene()->FindObject(L"UIObj", UILayer);
	Autoptr<NTTextWindow> TextWindow = UI->GetComponent<NTTextWindow>();
	TextWindow->CloseText();
	Autoptr<NTFadeRect> FadeRect = UI->GetComponent<NTFadeRect>();
	FadeRect->SetSpeed(Speed);
	FadeRect->StartFadeOut();
	GameSystem::SetInputable(false);
	return true;
}

bool NTEventSystem::MapChangeRelayEvent(void * _Cond1, void * _Cond2, void * _Func)
{
	if (_Func == nullptr)
	{
		return false;
	}

	bool Cond1 = *(bool*)_Cond1;
	float Cond2 = *(float*)_Cond2;
	Autoptr<NTEvent> Event = (NTEvent*)_Func;

	if (_Cond1 == nullptr)
	{
		Cond1 = true;
	}

	if (_Cond2 == nullptr)
	{
		return false;
	}

	if (Cond1 == true && Cond2 >= 1.0f && Event->IsActivated() == false)
	{
		Event->ActivateEvent();
	}
	return true;
}

bool NTEventSystem::FadeInEvent(void * _Speed, void * _Unuse1, void * _Unuse2)
{
	float Speed = 0.0f;
	if (_Speed != nullptr)
	{
		Speed = *(float*)_Speed;
	}
	else
		Speed = 1.0f;

	Autoptr<NTObject> UI = NTWinShortCut::GetMainSceneSystem().GetCurScene()->FindObject(L"UIObj", UILayer);
	Autoptr<NTFadeRect> FadeRect = UI->GetComponent<NTFadeRect>();
	FadeRect->SetSpeed(Speed);
	FadeRect->StartFadeIn();
	GameSystem::SetInputable(true);
	return true;
}

bool NTEventSystem::IsEqualEvent(void * _A, void * _B, void * _Size)
{
	int Size = *(int*)_Size;

	if (Size > 64)
	{
		return false;
	}

	__int64 ValueA;
	memset(&ValueA, 0, sizeof(__int64));
	memcpy_s(&ValueA, Size, _A, Size);
	__int64 ValueB;
	memset(&ValueB, 0, sizeof(__int64));
	memcpy_s(&ValueB, Size, _B, Size);


	if (ValueA == ValueB)
	{
		return true;
	}

	return false;
}

bool NTEventSystem::IsBiggerIntEvent(void * _A, void * _B, void * _UseEqual)
{
	int ValueA = *(int*)_A;
	int ValueB = *(int*)_B;
	bool Equal = *(bool*)_UseEqual;

	if (Equal == true)
	{
		if (ValueA >= ValueB)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (ValueA > ValueB)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool NTEventSystem::IsSmallerIntEvent(void * _A, void * _B, void * _UseEqual)
{
	int ValueA = *(int*)_A;
	int ValueB = *(int*)_B;
	bool Equal = *(bool*)_UseEqual;

	if (Equal == true)
	{
		if (ValueA <= ValueB)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (ValueA < ValueB)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool NTEventSystem::IsBiggerFloatEvent(void * _A, void * _B, void * _UseEqual)
{
	float ValueA = *(float*)_A;
	float ValueB = *(float*)_B;
	bool Equal = *(bool*)_UseEqual;

	if (Equal == true)
	{
		if (ValueA >= ValueB)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (ValueA > ValueB)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool NTEventSystem::IsSmallerFloatEvent(void * _A, void * _B, void * _UseEqual)
{
	float ValueA = *(float*)_A;
	float ValueB = *(float*)_B;
	bool Equal = *(bool*)_UseEqual;

	if (Equal == true)
	{
		if (ValueA <= ValueB)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (ValueA < ValueB)
		{
			return true;
		}
		return false;
	}

	return false;
}
