#include "NTTextWindow.h"
#include <NTSecondUVRenderer.h>
#include <DebugFunc.h>
#include "GameSystem.h"
#include <NTWinShortCut.h>




NTTextWindow::NTTextWindow() : Renderer(nullptr), MaxUv(0.0f), CurUv(0.0f), Open(false), Close(false), Speed(0.5f), TextSwitch(false)
{
}


NTTextWindow::~NTTextWindow()
{
}

bool NTTextWindow::Init(int _Order)
{
	Renderer = AddComponent<NTSecondUVRenderer>(_Order);
	Renderer->SetSubScale({ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() * 0.25f });
	Renderer->SetSubPivot({ 0.0f, -288.0f });
	Renderer->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Renderer->SetImageIndex(GameSystem::GetWindowStyle());
	MaxUv = Renderer->GetSecondUV();

	FontRenderer = AddComponent<NTFontRenderer>(L"±Ã¼­", _Order);
	FontRenderer->SetSubPivot({ 525.0f , 760.0f });
	FontRenderer->SetSubScale({ NTWinShortCut::GetMainWindow().GetWidthf() - 50.0f, 300.0f });
	FontRenderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	FontRenderer->SetSize(25.0f);
	FontRenderer->SetFontMode(NTFontRenderer::RENDERMODE::RM_RECT);
	
	return true;
}

bool NTTextWindow::Init(const wchar_t * _ImgName, int _Order)
{
	Renderer = AddComponent<NTSecondUVRenderer>(_ImgName, _Order);
	Renderer->SetSubScale({ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() * 0.37f });
	Renderer->SetSubPivot({ 0.0f, -288.0f });
	Renderer->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Renderer->SetImageIndex(GameSystem::GetWindowStyle());
	MaxUv = Renderer->GetSecondUV();

	FontRenderer = AddComponent<NTFontRenderer>(L"±Ã¼­", _Order);
	FontRenderer->SetSubPivot({ 525.0f , 760.0f });
	FontRenderer->SetSubScale({ NTWinShortCut::GetMainWindow().GetWidthf() - 75.0f, 300.0f });
	FontRenderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	FontRenderer->SetSize(40.0f);
	FontRenderer->SetFontMode(NTFontRenderer::RENDERMODE::RM_RECT);
	return true;
}

void NTTextWindow::MainUpdate()
{
	if (Open == true)
	{
		GameSystem::SetTextWindowStatus(true);
		if (CurUv < MaxUv)
		{
			CurUv += TimeSystem::DeltaTime() * Speed;
			Renderer->SetSecondUV(CurUv);
		}
		else
		{
			CurUv = MaxUv;
			Open = false;
			TextSwitch = true;
			
		}
	}

	if (Close == true)
	{
		TextSwitch = false;
		if (CurUv > 0.0f)
		{
			CurUv -= TimeSystem::DeltaTime() * Speed;
			Renderer->SetSecondUV(CurUv);
		}
		else
		{
			CurUv = 0.0f;
			Close = false;
			Renderer->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			GameSystem::SetTextWindowStatus(false);
		}
	}

	if (TextSwitch == true)
	{
		FontRenderer->SetUpdate(true);
	}
	else
	{
		FontRenderer->SetUpdate(false);
	}
}

void NTTextWindow::DbgRender()
{

}

void NTTextWindow::OpenText()
{
	Renderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	if (Close == true)
	{
		return;
	}

	Open = true;
}

void NTTextWindow::SetStyle(int _Index)
{
	if (_Index > (int)Renderer->GetImage()->GetCutCount() - 1)
	{
		_Index = Renderer->GetImage()->GetCutCount() - 1;

	}

	GameSystem::SetWindowStyle(_Index);
	Renderer->SetImageIndex(_Index);
}

void NTTextWindow::SetString(const wchar_t* _String)
{
	FontRenderer->SetString(_String);
}

void NTTextWindow::SetColor(unsigned __int8 R, unsigned __int8 G, unsigned __int8 B, unsigned __int8 A)
{
	FontRenderer->SetColor(R, G, B, A);
}

void NTTextWindow::SetColor(int _Color)
{
	FontRenderer->SetColor(_Color);
}

void NTTextWindow::SetFontSize(float _Size)
{
	FontRenderer->SetSize(_Size);
}

void NTTextWindow::SetFontPos(NTVEC _Pos)
{
	FontRenderer->SetSubPivot(_Pos);
}

void NTTextWindow::SetFontScale(NTVEC _Scale)
{
	FontRenderer->SetSubScale(_Scale);
}

void NTTextWindow::SetWindowPos(NTVEC _Pos)
{
	Renderer->SetSubPivot(_Pos);
}

void NTTextWindow::SetWindowScale(NTVEC _Scale)
{
	Renderer->SetSubScale(_Scale);
}

void NTTextWindow::SetWindowColor(NTCOLOR _Color)
{
	Renderer->SetColor(_Color);
}
