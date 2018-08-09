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
		NRT_MAX
	};

	enum NPCEVENTTYPE
	{
		NET_CONVERSATION,
		NET_SHOP,
		NET_MAX,
	};
private:
	Autoptr<NTSpRenderer> Renderer;
	Autoptr<NT2DCollision> Collider;
	Autoptr<NTSpFrameAnimator> Animator;
	Autoptr<NTEvent> Event;
		
	NPCRENDERTYPE RType;
	NPCEVENTTYPE EType;
	size_t CurTextCount;
	std::vector<int> TextIndex;

public:
	void AddText(int _Index)
	{
		TextIndex.push_back(_Index);
	}

	void SetTextCount(int _Count)
	{
		CurTextCount = _Count;
	}

	int GetTextCount()
	{
		return CurTextCount;
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