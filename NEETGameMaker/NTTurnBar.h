#pragma once
#include <NTLogic.h>

class NTSpRenderer;
class NTColorMeshRenderer;
class NTTurnBar : public NTLogic
{
private:
	Autoptr<NTSpRenderer> Bar;
	Autoptr<NTColorMeshRenderer> Gauge;
	float Percentage;
public:
	bool Init(int _Order = 0);
	void MainUpdate() override;
	void DbgRender() override;

	void HideBar();
	void ShowBar();
	void SetPercentage(float _Value)
	{
		Percentage = _Value;
	}
public:
	NTTurnBar();
	~NTTurnBar();
};

