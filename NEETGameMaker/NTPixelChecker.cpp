#include "NTPixelChecker.h"
#include <NTSpRenderer.h>
#include <DebugFunc.h>



bool NTPixelChecker::Init()
{
	return true;
}

void NTPixelChecker::MainUpdate()
{
	if (Renderer == nullptr)
	{
		return;
	}
	NTVEC2 OriginSize = Renderer->GetImage()->GetTex()->GetImageSize();
	NTVEC RenderScale = Renderer->GetWorldSubScale();

	CorrectionX = OriginSize.x / RenderScale.x;
	CorrectionY = OriginSize.y / RenderScale.y;
}

void NTPixelChecker::DbgRender()
{

}

void NTPixelChecker::SetRenderer(Autoptr<NTSpRenderer> _Renderer)
{
	Renderer = _Renderer;
}

Autoptr<NTSpRenderer> NTPixelChecker::GetRenderer()
{
	return Renderer;
}

NTCOLOR NTPixelChecker::GetPixelColor(float _X, float _Y)
{
	if (Renderer == nullptr)
	{
		return 0;
	}

	NTVEC RenderScale = Renderer->GetWorldSubScale();
	NTVEC2 OriginSize = Renderer->GetImage()->GetTex()->GetImageSize();

	float ActualX = RenderScale.x * 0.5f + _X;
	float ActualY = RenderScale.y * 0.5f + _Y;

	ActualY = -ActualY + RenderScale.y;
	

	if (ActualX * CorrectionX > OriginSize.x || ActualX * CorrectionX < 0)
	{
		return 0;
	}

	if (ActualY * CorrectionY > OriginSize.y || ActualY * CorrectionY < 0)
	{
		return 0;
	}

	return Renderer->GetImage()->GetTex()->GetPixel((int)(ActualX * CorrectionX), (int)(ActualY * CorrectionY));
}

NTCOLOR NTPixelChecker::GetPixelColor(NTVEC _Vec)
{
	return GetPixelColor(_Vec.x, _Vec.y);
}

NTPixelChecker::NTPixelChecker() : Renderer(nullptr), CorrectionX(0), CorrectionY(0)
{
}


NTPixelChecker::~NTPixelChecker()
{
}
