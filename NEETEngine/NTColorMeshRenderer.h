#pragma once
#include "NTRenderer.h"
class NTColorMeshRenderer : public NTRenderer
{
private:
	NTCOLOR Alpha;

public:
	void SetAlpha(float _Alpha)
	{
		Alpha.a = _Alpha;
	}

	float GetAlpha()
	{
		return Alpha.a;
	}

	NTCOLOR GetColor()
	{
		return Alpha;
	}
public:
	bool Init(int _Order = 0) override;
	void Render(const NTMAT& _VP) override;
public:
	NTColorMeshRenderer();
	~NTColorMeshRenderer();
};

