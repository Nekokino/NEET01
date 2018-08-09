#pragma once
#include "NTShader.h"

class NTPixelShader : public NTShader
{
private:
	ID3D11PixelShader* Shader;

public:
	bool Load(const char* _FuncName, UINT _VH = 5, UINT _VL = 0);
	void Update() override;

public:
	NTPixelShader();
	~NTPixelShader();
};

