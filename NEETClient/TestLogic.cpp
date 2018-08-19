#include "TestLogic.h"
#include <NTSpRenderer.h>
#include <InputSystem.h>


const NTVEC OriginPos = { 370.0f, 445.0f, 5.0f };
NTVEC TmpVec[7] = {  };
NTVEC TmpVec2[5] = {};
const NTVEC TmpVec3 = { 50.0f, 140.0f, 0.0f };
bool TestLogic::Init()
{
	Transform->SetLocalPosition({ 370.0f, 800.0f, 5.0f });
	Transform->SetLocalScale({ 2.0f, 2.0f, 1.0f });

	Pendulum = AddComponent<NTSpRenderer>(L"Pendulum.png");
	Pendulum->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Pendulum->SetSubPivot({ 0.0f, -420.0f, 10.0f });
	Pendulum->SetSubScale({ 236.0, 848.0f, 1.0f });

	BigC = AddComponent<NTSpRenderer>(L"BigC.png");
	BigC->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	BigC->SetSubPivot({ 298.0f, -130.0f, 10.0f });
	BigC->SetSubScale({ 192.0f, 352.0f, 1.0f });
	BigC->SetColor({1.0f, 1.0f, 1.0f, 0.0f});

	Trigger = AddComponent<NTSpRenderer>(L"T_Trigger.png");
	Trigger->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	Trigger->SetSubPivot({ 1300.0f, 140.0f, 0.0f });
	Trigger->SetSubScale({ 736.0f, 120.0f, 1.0f });

	ClockHand = AddComponent<NTSpRenderer>(L"ClockHand.png");
	ClockHand->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	ClockHand->SetSubPivot({ -335.0f, 135.0f, 0.0f });
	ClockHand->SetSubScale({ 136.0f, 144.0f, 1.0f });
	ClockHand->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	Logo = AddComponent<NTSpRenderer>(L"SquareLogo.png");
	Logo->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	Logo->SetSubPivot({ 0.0f, -280.0f, 0.0f });
	Logo->SetSubScale({ 344.0f, 32.0f, 1.0f });
	Logo->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });


	TmpVec[0] = NTVEC{ cosf(42.0f * MathSystem::D2R), sinf(42.0f * MathSystem::D2R), 0.0f };
	TmpVec[1] = NTVEC{ cosf(35.0f * MathSystem::D2R), sinf(35.0f * MathSystem::D2R), 0.0f };
	TmpVec[2] = NTVEC{ cosf(28.0f * MathSystem::D2R), sinf(28.0f * MathSystem::D2R), 0.0f };
	TmpVec[3] = NTVEC{ cosf(21.0f * MathSystem::D2R), sinf(21.0f * MathSystem::D2R), 0.0f };
	TmpVec[4] = NTVEC{ cosf(14.0f * MathSystem::D2R), sinf(14.0f * MathSystem::D2R), 0.0f };
	TmpVec[5] = NTVEC{ cosf(7.0f * MathSystem::D2R), sinf(7.0f * MathSystem::D2R), 0.0f };
	TmpVec[6] = NTVEC{ cosf(0.0f * MathSystem::D2R), sinf(0.0f * MathSystem::D2R), 0.0f };

	for (size_t i = 0; i < 7; ++i)
	{
		TmpVec[i] *= 580.0f;
		TmpVec[i] += OriginPos;
	}

	TmpVec2[0] = NTVEC{ -220.0f, 250.0f, 0.0f };
	TmpVec2[1] = NTVEC{ -155.0f, 250.0f, 0.0f };
	TmpVec2[2] = NTVEC{ -90.0f, 250.0f, 0.0f };
	TmpVec2[3] = NTVEC{ -15.0f, 250.0f, 0.0f };
	TmpVec2[4] = NTVEC{ 55.0f, 250.0f, 0.0f };


	hrono[0] = AddComponent<NTSpRenderer>(L"T_H.png");
	hrono[0]->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	hrono[0]->SetSubPivot({ -280.0f, 250.0f, 0.0f });
	hrono[0]->SetSubScale({ 60.0f, 88.0f, 1.0f });
	hrono[0]->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	hrono[1] = AddComponent<NTSpRenderer>(L"T_R.png");
	hrono[1]->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	hrono[1]->SetSubPivot({ -270.0f, 250.0f, 0.0f });
	hrono[1]->SetSubScale({ 64.0f, 88.0f, 1.0f });
	hrono[1]->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	hrono[2] = AddComponent<NTSpRenderer>(L"T_O1.png");
	hrono[2]->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	hrono[2]->SetSubPivot({ -260.0f, 250.0f, 0.0f });
	hrono[2]->SetSubScale({ 84.0f, 88.0f, 1.0f });
	hrono[2]->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	hrono[3] = AddComponent<NTSpRenderer>(L"T_N.png");
	hrono[3]->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	hrono[3]->SetSubPivot({ -250.0f, 250.0f, 0.0f });
	hrono[3]->SetSubScale({ 60.0f, 88.0f, 1.0f });
	hrono[3]->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	hrono[4] = AddComponent<NTSpRenderer>(L"T_O2.png");
	hrono[4]->SetMode(NTSubTransform::SUBMODE::SM_INDEPENDENT);
	hrono[4]->SetSubPivot({ -240.0f, 250.0f, 0.0f });
	hrono[4]->SetSubScale({ 84.0f, 88.0f, 1.0f });
	hrono[4]->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

	return true;
}

void TestLogic::MainUpdate()
{
	static float PenTime = 0.0f;
	bool CMove = true;
	bool hronoMove = true;
	bool TriggerMove = true;
	bool HandMove = true;
	PenTime += TimeSystem::DeltaTime();
	float PenRad = 0.0f;

	if (PenTime <= 9.0f)
	{
		static float PenScale = 2.0f;
		if (PenScale <= 2.0f && PenScale > 1.0f)
		{
			PenScale -= TimeSystem::DeltaTime() * 0.13f;
		}

		if (Transform->GetLocalPosition().y > OriginPos.y)
		{
			Transform->SetLocalMove(NTVEC::DOWN * TimeSystem::DeltaTime() * 50.0f);
		}
		Transform->SetLocalScale({ PenScale, PenScale, 0.0f, 0.0f });
	}

	if (PenTime <= 1.8f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[0], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 1.8f && PenTime <= 3.0f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[1], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 3.0f && PenTime <= 4.2f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[2], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 4.2f && PenTime <= 5.4f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[3], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 5.4f && PenTime <= 6.6f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[4], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 6.6f && PenTime <= 7.8f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[5], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 7.8f && PenTime <= 9.0f)
	{
		NTVEC PenPos = MathSystem::Pendulum(OriginPos, TmpVec[6], 4000.0f, 0.0f, PenTime);
		PenRad = MathSystem::GetRadian2D(PenPos, NTVEC::DOWN);
	}
	else if (PenTime > 9.0f)
	{
		BigC->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		NTVEC Dir = { -350.0f, 200.0f, 10.0f };
		Dir -= BigC->GetSubPivot();
		Dir.Normalize();
		if (MathSystem::GetLength2D(NTVEC{ -350.0f, 200.0f, 0.0f } - BigC->GetSubPivot()) <= 10)
		{
			static float CTime = 0.0f;
			CTime += TimeSystem::DeltaTime();
			if (CTime >= 1.0f)
			{
				CMove = false;
			}
		}
		else
		{
			BigC->SetSubMove(Dir * TimeSystem::DeltaTime() * 500.0f);
		}
	}
	
	if (CMove == false)
	{
		int EndCount = 0;
		for (size_t i = 0; i < 5; i++)
		{
			hrono[i]->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		}

		for (size_t i = 0; i < 5; i++)
		{
			if (hrono[i]->GetSubPivot().x < TmpVec2[i].x)
			{
				float Speed = 85.0f + i * 90.0f;
				hrono[i]->SetSubMove(NTVEC::RIGHT * Speed * TimeSystem::DeltaTime());
			}
			else
			{
				++EndCount;
			}
		}

		if (EndCount == 5)
		{
			hronoMove = false;
		}
	}

	if (hronoMove == false)
	{
		if (Trigger->GetSubPivot().x > TmpVec3.x)
		{
			Trigger->SetSubMove(NTVEC::LEFT * 400.0f * TimeSystem::DeltaTime());
		}
		else
		{
			TriggerMove = false;
		}
	}

	if (TriggerMove == false)
	{
		static float HandAlpha = 0.0f;
		if (HandAlpha <= 1.0f)
		{
			HandAlpha += TimeSystem::DeltaTime() * 5.0f;
		}
		else
		{
			HandMove = false;
		}
		ClockHand->SetColor({ 1.0f, 1.0f, 1.0f, HandAlpha });
	}

	if (HandMove == false)
	{
		static float LogoTime = 0.0f;
		LogoTime += TimeSystem::DeltaTime();
		if (LogoTime >= 4.0f)
		{
			static float LogoAlpha = 0.0f;
			if (LogoAlpha <= 1.0f)
			{
				LogoAlpha += TimeSystem::DeltaTime() * 2.0f;
			}
			Logo->SetColor({ 1.0f, 1.0f, 1.0f, LogoAlpha });
		}
	}
	Transform->SetLocalRotation({ 0.0f, 0.0f, PenRad });
}

TestLogic::TestLogic() : Pendulum(nullptr), BigC(nullptr), Trigger(nullptr), ClockHand(nullptr), Logo(nullptr)
{
	memset(hrono, 0, sizeof(hrono));
}


TestLogic::~TestLogic()
{
}
