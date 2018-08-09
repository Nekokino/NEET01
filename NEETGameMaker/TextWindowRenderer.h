#pragma once
#include <NTSpRenderer.h>
#include <RefNAutoptr.h>


class TextWindowRenderer : public NTSpRenderer
{
public:
	float SecondUv;
//public:
//	void Render(const NTMAT& _VP) override;
public:
	TextWindowRenderer();
	~TextWindowRenderer();
};

