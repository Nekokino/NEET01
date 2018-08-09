#pragma once
#include "NTComponent.h"
#include "RefNAutoptr.h"
#include <unordered_map>

class NTSpRenderer;
class NTSpFrameAnimator : public NTComponent
{
private:
	class SpriteAnimation : public RefCounter
	{
	public:
		friend NTSpFrameAnimator;

	private:
		std::wstring AnimationName;
		std::wstring ImageName;
		size_t StartFrame;
		size_t EndFrame;
		size_t Interval;
		float FrameSpeed;
		bool Loop;
	};

private:
	Autoptr<NTSpRenderer> SpRenderer;
	Autoptr<SpriteAnimation> CurAnimation;
	size_t CurFrame;
	float CurFrameTime;
	bool IsPause;
	std::unordered_map<std::wstring, Autoptr<SpriteAnimation>> AnimationMap;

public:
	void MainUpdate();

	void SetSpRenderer(Autoptr<NTSpRenderer> _SpRender);
	Autoptr<NTSpRenderer> GetSpRenderer();
	bool CreateAnimation(const wchar_t* _AnimationName, size_t _Start, size_t _End, float FrameSpeed, bool _Loop);
	bool ChangeAnimation(const wchar_t* _AnimationName, size_t _StartIndex = 0);
	void ChangeFrame(size_t _Frame);
	void PauseAnimation();
	void ResumeAnimation();
public:
	NTSpFrameAnimator();
	~NTSpFrameAnimator();
};

