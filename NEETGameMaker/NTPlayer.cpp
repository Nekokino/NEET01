#include "NTPlayer.h"

#include <CustomMacro.h>
#include <NTSpRenderer.h>
#include <NT2DCollision.h>
#include <NTSpFrameAnimator.h>
#include <InputSystem.h>
#include <NTScene.h>

#include "NTPixelCollider.h"
#include "NTTextWindow.h"


NTPlayer::NTPlayer() : Renderer(nullptr), Collider(nullptr), Status(nullptr), FieldSpeed(200.0f), Direction(PD_DOWN), EventCollider(nullptr), Animator(nullptr), PixelCollider(nullptr)
{
	
}


NTPlayer::~NTPlayer()
{
}

bool NTPlayer::Init(GameSystem::CHARACTER _Chara)
{
	Character = _Chara;
	Status = GameSystem::GetStatus(Character);
	Status->IsFront = true;
	switch (Character)
	{
	case GameSystem::CHRONO:
		break;
	case GameSystem::LUCCA:
		break;
	case GameSystem::MARU: 
		break;
	case GameSystem::KAERU:
		Renderer = AddComponent<NTSpRenderer>(L"Kaeru.png");
		Collider = AddComponent<NT2DCollision>(PlayerLayer);
		Collider->SetMode(COLTYPE::CT_2D_RECT);
		Animator = AddComponent<NTSpFrameAnimator>();
		Animator->SetSpRenderer(Renderer);
#pragma region Kaeru_Animation_Create
		Animator->CreateAnimation(L"WalkDown", 0, 6, DFS, true);
		Animator->CreateAnimation(L"WalkUp", 7, 13, DFS, true);
		Animator->CreateAnimation(L"WalkLeft", 14, 20, DFS, true);
		Animator->CreateAnimation(L"WalkRight", 21, 27, DFS, true);
		Animator->CreateAnimation(L"RunDown", 74, 77, DFS, true);
		Animator->CreateAnimation(L"RunUp", 78, 81, DFS, true);
		Animator->CreateAnimation(L"RunLeft", 82, 85, DFS, true);
		Animator->CreateAnimation(L"RunRight", 86, 89, DFS, true);

#pragma endregion
		Animator->ChangeAnimation(L"WalkDown");
		break;
	case GameSystem::ROBO:
		break;
	case GameSystem::EIRA:
		break;
	case GameSystem::MAOU:
		break;
	default:
		tassert(true);
		return false;
		break;
	}

	GetNTObject()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	GetNTObject()->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });

	Renderer->SetSubScale({ 400.0f, 400.0f, 1.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
	Collider->EnterFunc<NTPlayer>(this, &NTPlayer::ColEnter);
	Collider->ExitFunc<NTPlayer>(this, &NTPlayer::ColExit);
	Collider->SetName(L"MainCollider");

	PixelCollider = AddComponent<NTPixelCollider>();

	return true;
}

void NTPlayer::PreUpdate()
{
	if (EventCollider != nullptr)
	{
		EventCollider->Death();
		EventCollider = nullptr;
	}
	
}

bool Temp = false;

void NTPlayer::MainUpdate()
{
	if (Status->IsFront == true && GameSystem::GetInputable() == true)
	{
		if (true == InputSystem::IsPressed(L"Key2"))
		{
			if (true == InputSystem::IsPressed(L"ArrowUp"))
			{
				Animator->ChangeAnimation(L"RunUp");
				if (PixelCollider->MoveColCheck(NTVEC::UP, TimeSystem::DeltaTime() * FieldSpeed * 2.0f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, TimeSystem::DeltaTime() * FieldSpeed * 2.0f, 0.0f });
					Direction = PD_UP;
				}
				
			}

			if (true == InputSystem::IsPressed(L"ArrowDown"))
			{
				Animator->ChangeAnimation(L"RunDown");
				if (PixelCollider->MoveColCheck(NTVEC::DOWN, TimeSystem::DeltaTime() * FieldSpeed * 2.0f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, TimeSystem::DeltaTime() * -FieldSpeed * 2.0f, 0.0f });
					Direction = PD_DOWN;
				}
			}

			if (true == InputSystem::IsPressed(L"ArrowLeft"))
			{
				Animator->ChangeAnimation(L"RunLeft");
				if (PixelCollider->MoveColCheck(NTVEC::LEFT, TimeSystem::DeltaTime() * FieldSpeed * 2.0f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ TimeSystem::DeltaTime() * -FieldSpeed * 2.0f, 0.0f, 0.0f });
					Direction = PD_LEFT;
				}
			}

			if (true == InputSystem::IsPressed(L"ArrowRight"))
			{
				Animator->ChangeAnimation(L"RunRight");
				if (PixelCollider->MoveColCheck(NTVEC::RIGHT, TimeSystem::DeltaTime() * FieldSpeed * 2.0f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ TimeSystem::DeltaTime() * FieldSpeed * 2.0f, 0.0f, 0.0f });
					Direction = PD_RIGHT;
				}
			}
		}
		else
		{
			if (true == InputSystem::IsPressed(L"ArrowUp"))
			{
				Animator->ChangeAnimation(L"WalkUp");
				if (PixelCollider->MoveColCheck(NTVEC::UP, TimeSystem::DeltaTime() * FieldSpeed) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, TimeSystem::DeltaTime() * FieldSpeed, 0.0f });
					Direction = PD_UP;
				}
			}

			if (true == InputSystem::IsPressed(L"ArrowDown"))
			{
				Animator->ChangeAnimation(L"WalkDown");
				if (PixelCollider->MoveColCheck(NTVEC::DOWN, TimeSystem::DeltaTime() * FieldSpeed) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, TimeSystem::DeltaTime() * -FieldSpeed, 0.0f });
					Direction = PD_DOWN;
				}
			}

			if (true == InputSystem::IsPressed(L"ArrowLeft"))
			{
				Animator->ChangeAnimation(L"WalkLeft");
				if (PixelCollider->MoveColCheck(NTVEC::LEFT, TimeSystem::DeltaTime() * FieldSpeed) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ TimeSystem::DeltaTime() * -FieldSpeed, 0.0f, 0.0f });
					Direction = PD_LEFT;
				}
			}

			if (true == InputSystem::IsPressed(L"ArrowRight"))
			{
				if (PixelCollider->MoveColCheck(NTVEC::RIGHT, TimeSystem::DeltaTime() * FieldSpeed) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove({ TimeSystem::DeltaTime() * FieldSpeed, 0.0f, 0.0f });
					Direction = PD_RIGHT;
				}
				Animator->ChangeAnimation(L"WalkRight");
			}
		}
		if (true == InputSystem::IsUp(L"ArrowUp"))
		{
			Animator->ChangeAnimation(L"WalkUp");
			Animator->ChangeFrame(0);
			Animator->PauseAnimation();
		}

		if (true == InputSystem::IsUp(L"ArrowDown"))
		{
			Animator->ChangeAnimation(L"WalkDown");
			Animator->ChangeFrame(0);
			Animator->PauseAnimation();
		}

		if (true == InputSystem::IsUp(L"ArrowLeft"))
		{
			Animator->ChangeAnimation(L"WalkLeft");
			Animator->ChangeFrame(0);
			Animator->PauseAnimation();
		}

		if (true == InputSystem::IsUp(L"ArrowRight"))
		{
			Animator->ChangeAnimation(L"WalkRight");
			Animator->ChangeFrame(0);
			Animator->PauseAnimation();
		}

		if (true == InputSystem::IsDown(L"Key1"))
		{
			if (GameSystem::GetTextWindowStatus() == true) // 다음 대화가 없을때 라는 조건도 넣어줘야함.
			{
				if (GameSystem::GetNextText() == false)
				{
					Autoptr<NTSpRenderer> Tmp = GetScene()->RenderSystem.GetRenderer(L"TextWindow.png", UILayer);
					Autoptr<NTTextWindow> TextWindow = Tmp->GetNTObject()->GetComponent<NTTextWindow>();
					TextWindow->CloseText();
				}
				else
				{
					GameSystem::ActiveText();
				}
			}
			else
			{
				if (EventCollider != nullptr)
				{
					return;
				}
				else
				{
					EventCollider = AddComponent<NT2DCollision>(EventLayer);
				}

				NTVEC TmpVec = 0.0f;
				switch (Direction)
				{
				case NTPlayer::PD_DOWN:
					TmpVec.Pos = Collider->GetIndVec().Pos;
					TmpVec.Pos.y -= Collider->GetIndVec().Size.y * 0.5f;
					TmpVec.Size = NTVEC2{ Collider->GetIndVec().Size.x * 0.5f, 5.0f };
					EventCollider->SetMode(COLTYPE::CT_2D_RECT);
					EventCollider->SetRect(TmpVec);
					EventCollider->SetName(L"EventCollider");
					break;
				case NTPlayer::PD_LEFT:
					TmpVec.Pos = Collider->GetIndVec().Pos;
					TmpVec.Pos.x -= Collider->GetIndVec().Size.y * 0.5f;
					TmpVec.Size = NTVEC2{ Collider->GetIndVec().Size.x * 0.5f, 5.0f };
					EventCollider->SetMode(COLTYPE::CT_2D_RECT);
					EventCollider->SetRect(TmpVec);
					EventCollider->SetName(L"EventCollider");
					break;
				case NTPlayer::PD_UP:
					TmpVec.Pos = Collider->GetIndVec().Pos;
					TmpVec.Pos.y += Collider->GetIndVec().Size.y * 0.5f;
					TmpVec.Size = NTVEC2{ Collider->GetIndVec().Size.x * 0.5f, 5.0f };
					EventCollider->SetMode(COLTYPE::CT_2D_RECT);
					EventCollider->SetRect(TmpVec);
					EventCollider->SetName(L"EventCollider");
					break;
				case NTPlayer::PD_RIGHT:
					TmpVec.Pos = Collider->GetIndVec().Pos;
					TmpVec.Pos.x += Collider->GetIndVec().Size.y * 0.5f;
					TmpVec.Size = NTVEC2{ Collider->GetIndVec().Size.x * 0.5f, 5.0f };
					EventCollider->SetMode(COLTYPE::CT_2D_RECT);
					EventCollider->SetRect(TmpVec);
					EventCollider->SetName(L"EventCollider");
					break;
				case NTPlayer::PD_NONE:
				default:
					tassert(true);
					break;
				}
			}
		}
	}
}

void NTPlayer::DbgRender()
{

}

void NTPlayer::SetFieldRenderer(Autoptr<NTSpRenderer> _Renderer)
{
	PixelCollider->SetSourceRenderer(_Renderer);
}

void NTPlayer::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
}

void NTPlayer::ColExit(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
}

