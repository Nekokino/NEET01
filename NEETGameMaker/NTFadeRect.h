#pragma once
#include <NTLogic.h>

class NTColorMeshRenderer;
class NTFadeRect : public NTLogic
{
private:
	Autoptr<NTColorMeshRenderer> Renderer;

	float CurAlpha;
	float Speed;

	bool FadeInSwitch;
	bool FadeOutSwitch;
private:
	void FadeIn();
	void FadeOut();

public:
	void StartFadeIn()
	{
		FadeInSwitch = true;
	}
	void StartFadeOut()
	{
		FadeOutSwitch = true;
	}

	float GetCurAlpha()
	{
		return CurAlpha;
	}

	float* GetCurAlphaPointer() // ³ªÁß¿¡ ¾À¿¡ ÇÁ·»µå °É±â
	{
		return &CurAlpha;
	}

	bool Init(float _Alpha = 0.0f, float _Speed = 1.0f);
	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}
	void MainUpdate() override;
	void DbgRender() override;




	Autoptr<NTColorMeshRenderer> GetRenderer();
public:
	NTFadeRect();
	~NTFadeRect();
};

