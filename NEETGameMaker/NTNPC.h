#pragma once
#include <NTLogic.h>
#include "GameSystem.h"

class NPCData
{
public:
	int RenderType;
	int EventType;
	int TextSize;
	wchar_t Buf[256];
};

class NTSpRenderer;
class NT2DCollision;
class NTCollisionComponent;
class NTSpFrameAnimator;
class NTEvent;
class NTNPC : public NTLogic
{
public:
	enum NPCRENDERTYPE
	{
		NRT_AD_GREENGUY,
		NRT_AD_BROWNGUY,
		NRT_AD_REDGUY,
		NRT_AD_BLUEGUY,
		NRT_AD_GONZALEZ,
		NRT_MAX
	};

	enum NPCEVENTTYPE
	{
		NET_CONVERSATION,
		NET_CONVBATLLE,
		NET_SHOP,
		NET_MAX,
	};
private:
	Autoptr<NTSpRenderer> Renderer;
	Autoptr<NT2DCollision> Collider;
	Autoptr<NTSpFrameAnimator> Animator;
	std::list<Autoptr<NTEvent>> EventList;
		
	NPCRENDERTYPE RType;
	NPCEVENTTYPE EType;
	size_t CurListIndex;
	size_t CurTextCount;
	bool NextEvent;
	int EventCount;
	std::vector<int> StartText;
	std::vector<std::vector<int>> TextIndex;

public:
	void AddText(size_t _ListIndex, int _TextIndex)
	{
		TextIndex[_ListIndex].push_back(_TextIndex);
	}

	size_t AddTextList()
	{
		TextIndex.push_back(std::vector<int>());
		StartText.push_back(0);

		return TextIndex.size();
	}

	void SetTextCount(int _StartCount)
	{
		CurTextCount = _StartCount;
	}

	size_t GetTextCount()
	{
		return CurTextCount;
	}

	void SetStartCount(size_t _ListIndex, int _Value)
	{
		StartText[_ListIndex] = _Value;
	}

	void SetListIndex(size_t _ListIndex)
	{
		CurListIndex = _ListIndex;
	}

	bool Init(NPCRENDERTYPE _RType, NPCEVENTTYPE _EType);
	void MainUpdate() override;
	void DbgRender() override;

	void ActiveTextEvent();

public:
	void ColEnter(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColStay(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
public:
	NTNPC();
	~NTNPC();
};