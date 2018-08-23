#pragma once
#include <unordered_map>


// ����ٰ� �Լ��� ������Ÿ�Ե��� ����� ����
// NTEvent������ ���⼭ ���� Event�� �ʿ��ѵ����� �ʿ��� ã�Ƽ� �������༭ �浹�Ҷ� �Լ��� ����ǰ� �ϴ��� �ϸ� �ǰڴ�.

class NTEventSystem
{
public:
	static std::unordered_map<std::wstring, bool(*)(void*, void*, void*)> EventMap;

public:
	static void Init();

	static bool(*FindEvent(const wchar_t* _EventName))(void*, void*, void*)
	{
		std::unordered_map<std::wstring, bool(*)(void*, void*, void*)>::iterator FindIter = EventMap.find(_EventName);

		if (FindIter == EventMap.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	static bool ConversationEvent(void* _String, void* _Color = nullptr, void* _Unuse = nullptr);
	static bool MoveMapEvent(void* _MapName, void* _Position, void* _NextEvent);
	static bool FadeOutEvent(void* _Speed, void* _Unuse1 = nullptr, void* _Unuse2 = nullptr);
	static bool MapChangeRelayEvent(void* _Cond1, void* _Con2, void* _Func);
	static bool FadeInEvent(void* _Speed, void* _Unuse1 = nullptr, void* _Unuse2 = nullptr);
	static bool IsEqualEvent(void* _A, void* _B, void* _Size);
	static bool IsBiggerIntEvent(void* _A, void* _B, void* _UseEqual);
	static bool IsSmallerIntEvent(void* _A, void* _B, void* _UseEqual);
	static bool IsBiggerFloatEvent(void* _A, void* _B, void* _UseEqual);
	static bool IsSmallerFloatEvent(void* _A, void* _B, void* _UseEqual);
	static bool BattleEnterEvent(void* _A, void* _B, void* _C);
private:
	NTEventSystem() {};
	virtual ~NTEventSystem() = 0;
};
