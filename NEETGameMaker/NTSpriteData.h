#pragma once

class NTSpriteData
{
public:
	wchar_t PathName[256];
	wchar_t FileName[256];

	int CutX;
	int CutY;

	bool IsCut;
	
public:
	NTSpriteData() : CutX(1), CutY(1), IsCut(false)
	{

	}
};