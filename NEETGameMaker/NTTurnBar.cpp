#include "NTTurnBar.h"

#include "GameSystem.h"

#include <NTSpRenderer.h>
#include <NTColorMeshRenderer.h>

NTTurnBar::NTTurnBar() : Bar(nullptr), Gauge(nullptr), Percentage(0.0f)
{
}


NTTurnBar::~NTTurnBar()
{
}


bool NTTurnBar::Init(int _Order)
{
	Gauge = GetNTObject()->AddComponent<NTColorMeshRenderer>(_Order);
	Gauge->SetSubScale({ 0.0f, 24.0f, 1.0f });
	Gauge->SetSubPivot({-24.0f, 0.0f, 0.0f});
	Gauge->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Gauge->SetColor(1.0f);
	Bar = GetNTObject()->AddComponent<NTSpRenderer>(L"TurnBar.png", _Order);
	Bar->SetSubScale({ 64.0f, 32.0f, 1.0f});
	Bar->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	return true;
}

void NTTurnBar::MainUpdate()
{
	Gauge->SetSubScale({0.48f * Percentage, 24.0f, 1.0f});
	Gauge->SetSubPivot({-24.0f + Percentage * 0.24f, 0.0f, 0.0f});
}

void NTTurnBar::DbgRender()
{
}

void NTTurnBar::HideBar()
{
	Bar->SetColor(0.0f);
	Gauge->SetColor(0.0f);
}

void NTTurnBar::ShowBar()
{
	Bar->SetColor(1.0f);
	Gauge->SetColor(1.0f);
}
