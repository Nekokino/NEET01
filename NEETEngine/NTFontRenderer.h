#pragma once
#include "NTRenderer.h"
#include <string>

class NTFont;
class NTFontRenderer : public NTRenderer
{
public:
	enum RENDERMODE
	{
		RM_NORMAL,
		RM_RECT,
		RM_MAX,
	};
private:
	Autoptr<NTFont> Font;
	float Size;
	int Color;
	std::wstring String;
	RENDERMODE Mode;

public:
	bool Init(int _Order = 0) override;
	bool Init(const wchar_t* _FontName, int _Order = 0);
	void Render(const NTMAT& _VP) override;

	void SetString(const wchar_t* _String)
	{
		String = _String;
	}

	void SetColor(unsigned __int8 R, unsigned __int8 G, unsigned __int8 B, unsigned __int8 A)
	{
		Color = 0;
		int TempR = R;
		int TempG = G;
		int TempB = B;
		int TempA = A;

		Color |= TempR;
		Color |= (TempG << 8);
		Color |= (TempB << 16);
		Color |= (TempA << 24);
	}

	void SetColor(int _Color)
	{
		Color = _Color;
	}

	void SetSize(float _Size)
	{
		Size = _Size;
	}

	void SetFontMode(RENDERMODE _RM)
	{
		Mode = _RM;
	}

public:
	NTFontRenderer();
	~NTFontRenderer();
};

