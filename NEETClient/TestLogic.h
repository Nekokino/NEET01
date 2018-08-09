#pragma once
#include <NTLogic.h>

class NTSpRenderer;
class TestLogic : public NTLogic
{
private:
	Autoptr<NTSpRenderer> Pendulum;
	Autoptr<NTSpRenderer> BigC;
	Autoptr<NTSpRenderer> hrono[5];
	Autoptr<NTSpRenderer> Trigger;
	Autoptr<NTSpRenderer> ClockHand;
	Autoptr<NTSpRenderer> Logo;
public:
	bool Init() override;
	void MainUpdate() override;

public:
	TestLogic();
	~TestLogic();
};

