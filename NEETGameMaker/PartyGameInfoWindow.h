#pragma once
#include <NTLogic.h>

#define OriginPos { WinSize.x * -0.27f, WinSize.y * -0.3375f }

class NTFontRenderer;
class PartyGameInfoWindow : public NTLogic
{
private:
	NTVEC2 WinSize;
	Autoptr<NTFontRenderer> PlayTime;
	Autoptr<NTFontRenderer> Gold;
public:
	bool Init();
	void MainUpdate() override;
	void DbgUpdate() override;
public:
	PartyGameInfoWindow();
	~PartyGameInfoWindow();
};

