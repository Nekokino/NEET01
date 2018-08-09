#include "TextWindowRenderer.h"


TextWindowRenderer::TextWindowRenderer() : SecondUv(0.0f)
{
}


TextWindowRenderer::~TextWindowRenderer()
{
}

//void TextWindowRenderer::Render(const NTMAT & _VP)
//{
//	tassert(nullptr == Transform);
//	if (nullptr == Transform)
//	{
//		return;
//	}
//
//	if (nullptr == Image)
//	{
//		return;
//	}
//
//	SubTranformUpdate();
//
//
//
//
//	GetNTWindow()->GetDevice().SetData<NTMAT>(L"TRANS", (GetSubWorldMat() * _VP).RTranspose(), NTShader::STYPE::ST_VS);
//	GetNTWindow()->GetDevice().SetData<NTVEC>(L"IMGUV", Image->GetUv(ImgIndex), NTShader::STYPE::ST_PX);
//	GetNTWindow()->GetDevice().SetData<NTVEC>(L"SECONDUV", SecondUv, NTShader::STYPE::ST_PX);
//
//	Material->Update();
//	Image->GetSamp()->Update();
//	Image->GetTex()->Update();
//	Mesh->Update();
//	Mesh->Render();
//}