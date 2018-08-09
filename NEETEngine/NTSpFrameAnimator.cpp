#include "PreCom.h"
#include "NTSpFrameAnimator.h"
#include "StlAssist.h"
#include "NTSpRenderer.h"
#include "TimeSystem.h"


NTSpFrameAnimator::NTSpFrameAnimator() : SpRenderer(nullptr), IsPause(false)
{
}


NTSpFrameAnimator::~NTSpFrameAnimator()
{
}

void NTSpFrameAnimator::MainUpdate()
{
	if (nullptr != CurAnimation)
	{
		if (IsPause == false)
		{
			CurFrameTime += DTime;
		}
		else
		{
			CurFrameTime = 0.0f;
		}

			size_t Count = (size_t)(CurFrameTime / CurAnimation->FrameSpeed);

			if (0 < Count)
			{
				CurFrameTime -= CurAnimation->FrameSpeed * Count;
			}

			if (false == CurAnimation->Loop && CurAnimation->EndFrame <= CurFrame + Count)
			{
				CurFrame = CurAnimation->EndFrame;
				SpRenderer->SetImageIndex(CurFrame);
				return;
			}

			CurFrame += Count;

			if (CurAnimation->EndFrame + 1 <= CurFrame)
			{
				size_t a = Count;
				CurFrame = CurAnimation->StartFrame + ((CurFrame - CurAnimation->StartFrame) % CurAnimation->Interval); // ¿þ? 
			}

			SpRenderer->SetImageIndex(CurFrame);
	}
}

void NTSpFrameAnimator::SetSpRenderer(Autoptr<NTSpRenderer> _SpRender)
{
	SpRenderer = _SpRender;
}

Autoptr<NTSpRenderer> NTSpFrameAnimator::GetSpRenderer()
{
	return SpRenderer;
}

bool NTSpFrameAnimator::CreateAnimation(const wchar_t * _AnimationName, size_t _Start, size_t _End, float _FrameSpeed, bool _Loop)
{
	SpriteAnimation* NewAni = new SpriteAnimation();

	NewAni->AnimationName = _AnimationName;
	NewAni->ImageName = SpRenderer->GetImage()->GetName();
	NewAni->StartFrame = _Start;
	NewAni->EndFrame = _End;
	NewAni->Loop = _Loop;
	NewAni->FrameSpeed = _FrameSpeed;
	NewAni->Interval = _End - _Start + 1;

	AnimationMap.insert(std::unordered_map<std::wstring, Autoptr<SpriteAnimation>>::value_type(_AnimationName, NewAni));
	return true;
}

bool NTSpFrameAnimator::ChangeAnimation(const wchar_t * _AnimationName, size_t _StartIndex)
{
	tassert(nullptr == SpRenderer);

	Autoptr<SpriteAnimation> tmp = MapFind<Autoptr<SpriteAnimation>>(AnimationMap, _AnimationName);

	if (nullptr == tmp)
	{
		tassert(true);
		return false;
	}

	IsPause = false;

	if (CurAnimation == tmp)
	{
		return false;
	}

	CurAnimation = tmp;
	CurFrame = CurAnimation->StartFrame + _StartIndex;
	CurFrameTime = 0.0f;
	SpRenderer->SetImage(CurAnimation->ImageName.c_str());
	SpRenderer->SetImageIndex(CurFrame);
	return true;
}

void NTSpFrameAnimator::ChangeFrame(size_t _Frame)
{
	CurFrame = CurAnimation->StartFrame + _Frame;
}

void NTSpFrameAnimator::PauseAnimation()
{
	IsPause = true;
}

void NTSpFrameAnimator::ResumeAnimation()
{
	IsPause = false;
}
