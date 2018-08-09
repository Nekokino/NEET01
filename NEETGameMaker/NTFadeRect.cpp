#include "NTFadeRect.h"
#include "GameSystem.h"
#include <NTColorMeshRenderer.h>
#include <NTWindow.h>


Autoptr<NTColorMeshRenderer> NTFadeRect::GetRenderer()
{
	return Renderer;
}

NTFadeRect::NTFadeRect() : Speed(1.0f), CurAlpha(0.0f), FadeInSwitch(false), FadeOutSwitch(false), Renderer(nullptr)
{
}


NTFadeRect::~NTFadeRect()
{
}

void NTFadeRect::FadeIn()
{
	if (FadeInSwitch == false)
	{
		return;
	}

	CurAlpha = Renderer->GetAlpha();

	if (CurAlpha <= 0.0f)
	{
		return;
	}

	if (CurAlpha > 0.0f)
	{
		CurAlpha -= TimeSystem::DeltaTime();
	}

	if (CurAlpha < 0.0f)
	{
		CurAlpha = 0.0f;
		FadeInSwitch = false;
	}

	Renderer->SetAlpha(CurAlpha);
	
}

void NTFadeRect::FadeOut()
{
	if (FadeOutSwitch == false)
	{
		return;
	}

	CurAlpha = Renderer->GetAlpha();

	if (CurAlpha >= 1.0f)
	{
		return;
	}

	if (CurAlpha < 1.0f)
	{
		CurAlpha += TimeSystem::DeltaTime();
	}

	if (CurAlpha > 1.0f)
	{
		CurAlpha = 1.0f;
		FadeOutSwitch = false;
	}

	Renderer->SetAlpha(CurAlpha);
}

bool NTFadeRect::Init(float _Alpha, float _Speed)
{
	Renderer = AddComponent<NTColorMeshRenderer>(UILayer);

	Speed = _Speed;
	Renderer->SetAlpha(_Alpha);
	Renderer->SetSubPivot({ 0.0f, 0.0f, 1.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	Renderer->SetSubScale({ GetNTWindow()->GetWidthf(), GetNTWindow()->GetHeightf(), 1.0f });
	return true;
}

void NTFadeRect::MainUpdate()
{
	FadeIn();
	FadeOut();
}

void NTFadeRect::DbgRender()
{
}