#include "PreCom.h"
#include "NTFontRenderer.h"
#include "ResourceSystem.h"
#include "NTFont.h"
#include "NTWinShortCut.h"

NTFontRenderer::NTFontRenderer() : Font(nullptr), Color(0xffffffff), Size(0.0f), Mode(RM_MAX)
{
}


NTFontRenderer::~NTFontRenderer()
{
}

bool NTFontRenderer::Init(int _Order)
{
	NTRenderer::Init(_Order);

	return true;
}

bool NTFontRenderer::Init(const wchar_t* _FontName, int _Order)
{
	Font = ResourceSystem<NTFont>::Find(_FontName);

	if (false == Init(_Order))
	{
		return false;
	}

	if (Font == nullptr)
	{
		tassert(true);
		return false;
	}

	return true;
}

void NTFontRenderer::Render(const NTMAT & _VP)
{
	if (Mode == RM_MAX)
	{
		return;
	}

	if (String.size() <= 0)
	{
		return;
	}

	if (Size <= 0.0f)
	{
		return;
	}

	wchar_t* Tmp = const_cast<wchar_t*>(String.c_str());

	NTRECT Rect;
	Rect.Pos = GetSubPivot().Pos;
	Rect.Size = GetSubScale().Pos;

	if (Mode == RM_NORMAL)
	{
		Font->DrawFont(Tmp, GetSubPivot().Pos, Size, Color);
	}
	
	if (Mode == RM_RECT)
	{
		Font->DrawFontRect(Tmp, { GetSubPivot().Pos, GetSubScale().Pos }, Size, Color);
	}

	NTWinShortCut::GetMainDevice().ResetContext();
}
