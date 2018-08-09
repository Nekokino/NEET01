#include "NTPieceWindow.h"
#include "GameSystem.h"
#include <NTSpRenderer.h>


NTPieceWindow::NTPieceWindow()
{
}


NTPieceWindow::~NTPieceWindow()
{
}

bool NTPieceWindow::Init(size_t _Row, size_t _Col, float _Size)
{
	NTVEC Pos = GetNTObject()->GetTransform()->GetLocalPosition();
	int Style = GameSystem::GetWindowStyle();
	Autoptr<NTSpRenderer> LT = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
	LT->SetImageIndex(9 * Style + 0);
	LT->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	LT->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
	Autoptr<NTSpRenderer> RT = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
	RT->SetImageIndex(9 * Style + 2);
	RT->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	RT->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
	Autoptr<NTSpRenderer> LB = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
	LB->SetImageIndex(9 * Style + 6);
	LB->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	LB->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
	Autoptr<NTSpRenderer> RB = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
	RB->SetImageIndex(9 * Style + 8);
	RB->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	RB->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });

	LT->SetSubPivot({ -64.0f * _Row * _Size - 16.0f * _Size, 64.0f * _Col * _Size + 16.0f * _Size });
	RT->SetSubPivot({ 64.0f * _Row * _Size + 16.0f * _Size, 64.0f * _Col * _Size + 16.0f  * _Size });
	LB->SetSubPivot({ -64.0f * _Row * _Size - 16.0f * _Size, -64.0f * _Col * _Size - 16.0f * _Size });
	RB->SetSubPivot({ 64.0f * _Row * _Size + 16.0f * _Size, -64.0f * _Col * _Size - 16.0f * _Size });

	NTVEC Tmp1 = LT->GetSubPivot() - RT->GetSubPivot();
	float Tmp2 = ( MathSystem::GetLength(Tmp1) - 32.0f * _Size) / (64.0f * _Size);

	for (float i = 0; i < Tmp2; i++)
	{
		Autoptr<NTSpRenderer> Top = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
		Autoptr<NTSpRenderer> Bottom = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
		Top->SetImageIndex(9 * Style + 1);
		Bottom->SetImageIndex(9 * Style + 7);
		Top->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		Bottom->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		Top->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
		Bottom->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
		Top->SetSubPivot({ LT->GetSubPivot().x - 16.0f * _Size + (i + 1) * 64.0f * _Size, LT->GetSubPivot().y });
		Bottom->SetSubPivot({ LT->GetSubPivot().x - 16.0f * _Size + (i + 1) * 64.0f * _Size, LB->GetSubPivot().y });
	}

	Tmp1 = LT->GetSubPivot() - LB->GetSubPivot();
	Tmp2 = (MathSystem::GetLength(Tmp1) - 32.0f * _Size) / (64.0f * _Size);

	for (float i = 0; i < Tmp2; i++)
	{
		Autoptr<NTSpRenderer> Left = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
		Autoptr<NTSpRenderer> Right = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
		Left->SetImageIndex(9 * Style + 3);
		Right->SetImageIndex(9 * Style + 5);
		Left->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		Right->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		Left->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
		Right->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
		Left->SetSubPivot({ LT->GetSubPivot().x, LB->GetSubPivot().y - 16.0f * _Size + (i + 1) * 64.0f  * _Size });
		Right->SetSubPivot({ RT->GetSubPivot().x, LB->GetSubPivot().y - 16.0f * _Size + (i + 1) * 64.0f  * _Size });
	}

	for (size_t y = 0; y < _Col; y++)
	{
		for (size_t x = 0; x < _Row; x++)
		{
			Autoptr<NTSpRenderer> In = AddComponent<NTSpRenderer>(L"WindowPiece.png", UILayer);
			In->SetImageIndex(9 * Style + 4);
			In->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
			In->SetSubScale({ 128.0f * _Size, 128.0f * _Size, 1.0f });
			In->SetSubPivot({ LT->GetSubPivot().x - 48.0f * _Size + (x + 1) * 128.0f * _Size, LB->GetSubPivot().y - 48.0f * _Size + (y + 1) * 128.0f  * _Size });
		}
	}
	return true;
}

void NTPieceWindow::MainUpdate()
{
}

void NTPieceWindow::DbgRender()
{
}