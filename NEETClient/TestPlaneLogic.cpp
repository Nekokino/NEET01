#include "TestPlaneLogic.h"
#include <NTSpRenderer.h>
#include <InputSystem.h>
#include <NTSpFrameAnimator.h>
#include <NT2DCollision.h>
#include <DebugFunc.h>



TestPlaneLogic::TestPlaneLogic() : ImgIndex(0)
{
}


TestPlaneLogic::~TestPlaneLogic()
{
}

bool TestPlaneLogic::Init()
{
	ChRenderer = AddComponent<NTSpRenderer>(L"Kaeru.png");
	ChRenderer2 = AddComponent<NTSpRenderer>(L"Kaeru.png");
	//Collider = AddComponent<NT2DCollision>();

	Animator = AddComponent<NTSpFrameAnimator>();
	Animator->SetSpRenderer(ChRenderer2);
	Animator->CreateAnimation(L"test", 0, 5, 0.3f, true);
	Animator->ChangeAnimation(L"test");
	Transform->SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Transform->SetLocalPosition({ 0.0f, 0.0f, 10.0f });

	ChRenderer2->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	ChRenderer2->SetSubPivot({ 0.0f, 100.0f, 0.0f });
	ChRenderer2->SetSubScale({ 500.0f, 500.0f, 1.0f });

	//Collider->SetMode(COLTYPE::CT_2D_RECT);

	

	return true;
}

void TestPlaneLogic::MainUpdate()
{
	if (InputSystem::IsDown(L"ClearObj"))
	{
		GetNTObject()->Death();
	}


	if (InputSystem::IsPressed(L"U"))
	{
		Transform->SetLocalMove(NTVEC::UP * 100.0f * TimeSystem::DeltaTime());
	}

	if (InputSystem::IsPressed(L"D"))
	{
		Transform->SetLocalMove(NTVEC::DOWN * 100.0f * TimeSystem::DeltaTime());
	}

	if (InputSystem::IsPressed(L"L"))
	{
		Transform->SetLocalMove(NTVEC::LEFT * 100.0f * TimeSystem::DeltaTime());
	}

	if (InputSystem::IsPressed(L"R"))
	{
		Transform->SetLocalMove(NTVEC::RIGHT * 100.0f * TimeSystem::DeltaTime());
	}

	if (InputSystem::IsPressed(L"ZR"))
	{
		Transform->SetLocalAccRotation(NTVEC::RZ * 0.5f * TimeSystem::DeltaTime());
	}

	if (InputSystem::IsPressed(L"RZR"))
	{
		Transform->SetLocalAccRotation(NTVEC::RRZ * 0.5f * TimeSystem::DeltaTime());
	}

}

void TestPlaneLogic::DbgRender()
{
	DebugFunc::DrawFont(L"¤»", { 100.0f, 100.0f }, 50.0f, 0xffffffff);
}

void TestPlaneLogic::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	int a = 0;
}

void TestPlaneLogic::ColExit(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
	int a = 0;
}
