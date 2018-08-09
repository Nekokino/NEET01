#pragma once
#include <NTLogic.h>

class NTSpRenderer;
class NTPixelChecker : public NTLogic
{
private:
	Autoptr<NTSpRenderer> Renderer;
	float CorrectionX;
	float CorrectionY;
public:
	bool Init();
	void MainUpdate() override;
	void DbgRender() override;

	void SetRenderer(Autoptr<NTSpRenderer> _Renderer);
	Autoptr<NTSpRenderer> GetRenderer();
	NTCOLOR GetPixelColor(float _X, float _Y);
	NTCOLOR GetPixelColor(NTVEC _Vec);
public:
	NTPixelChecker();
	~NTPixelChecker();
};

