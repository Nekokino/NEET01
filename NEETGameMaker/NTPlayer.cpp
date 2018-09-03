#include "NTPlayer.h"

#include <CustomMacro.h>
#include <NTSpRenderer.h>
#include <NT2DCollision.h>
#include <NTSpFrameAnimator.h>
#include <InputSystem.h>
#include <NTScene.h>
#include <DebugFunc.h>

#include "NTPixelCollider.h"
#include "NTTextWindow.h"
#include "NTBattle.h"


NTPlayer::NTPlayer() : Renderer(nullptr), Collider(nullptr), Status(nullptr), FieldSpeed(200.0f), Direction(PD_DOWN), EventCollider(nullptr), Animator(nullptr), PixelCollider(nullptr), MoveToVec(0.0f), MoveSpeed(0.0f), DefaultSet(false), FrontPlayer(nullptr), bAttack(false), NextAni(nullptr)
 ,bReturn(false)
{
	AnimatorVector.reserve(CHARA_MAX);
}


NTPlayer::~NTPlayer()
{
}

void NTPlayer::SetRendererDefaultData()
{
	if (DefaultSet == true)
	{
		return;
	}
	DefaultSet = true;
	for (size_t i = 0; i < CHARA_MAX; i++)
	{
		Autoptr<NTSpFrameAnimator> TmpAnimator = AddComponent<NTSpFrameAnimator>();
		TmpAnimator->SetSpRenderer(Renderer);
		AnimatorVector.push_back(TmpAnimator);
	}
#pragma region ChronoAnimation
	Renderer->SetImage(L"Chrono.png");
	AnimatorVector[CHRONO]->CreateAnimation(L"IdleDown", 0, 2, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"IdleUp", 3, 3, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"IdleRight", 4, 6, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WalkDown", 7, 12, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WalkUp", 13, 18, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WalkRight", 19, 24, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"RunDown", 25, 26, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"RunUp", 27, 28, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"RunRight", 29, 30, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ArrestDown", 31, 32, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ArrestUp", 33, 34, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ArrestRight", 35, 36, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"NoDown", 37, 39, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"NoUp", 40, 42, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"NoRight", 43, 45, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"SurpriseDown", 46, 46, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"SurpriseRight", 47, 47, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ThinkDown", 48, 48, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ThinkUp", 49, 49, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"ThinkRight", 50, 50, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"HappyUp", 54, 57, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"HappyDown", 58, 59, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"HappyRight", 60, 61, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"AllHandDown", 62, 62, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"RightHandDown", 63, 63, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"LeftHandDown", 64, 64, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"AllHandUp", 65, 65, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"LeftHandUp", 66, 66, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"RightHandUp", 67, 67, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Wink", 68, 68, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Fighting", 69, 72, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"CrouchDown", 73, 73, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"CrouchRight", 74, 74, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Sleep", 75, 76, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Wakeup", 77, 79, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Drink", 80, 81, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"SitDown", 82, 82, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"SitPray", 83, 84, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"PrayDown", 85, 86, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"PrayUp", 87, 88, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"PrayRight", 89, 90, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"FlyPrayDown", 91, 92, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"FlyPrayUp", 93, 94, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"FlyPrayRight", 95, 96, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"DamageDown", 97, 97, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"DamageUp", 98, 98, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"DamageRight", 99, 99, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"Down", 100, 100, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponReadyDown", 101, 104, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponIdleDown", 105, 106, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponReadyUp", 107, 110, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponIdleUp", 111, 112, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponReadyLeft", 113, 116, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"WeaponIdleLeft", 117, 118, DFS, true);
	AnimatorVector[CHRONO]->CreateAnimation(L"HitDown", 119, 121, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"CriticalDown", 119, 123, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"HitUp", 124, 125, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"CriticalUp", 124, 127, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"HitRight", 125, 127, DFS, false);
	AnimatorVector[CHRONO]->CreateAnimation(L"CriticalRight", 125, 129, DFS, false);
#pragma endregion
#pragma region LuccaAnimation
	Renderer->SetImage(L"Lucca.png");
	AnimatorVector[LUCCA]->CreateAnimation(L"IdleDown", 0, 0, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"IdleUp", 1, 1, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"IdleRight", 2, 2, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WalkDown", 3, 8, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WalkUp", 9, 14, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WalkRight", 15, 20, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"RunDown", 21, 22, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"RunUp", 23, 26, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"RunRight", 27, 32, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"NoDown", 33, 35, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"NoUp", 36, 38, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"NoRight", 39, 41, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"SurpriseDown", 42, 42, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"SurpriseUp", 43, 43, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"SurpriseRight", 44, 44, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"ThinkDown", 45, 45, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"ThinkUp", 46, 46, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"ThinkRight", 47, 47, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"HappyUp", 51, 54, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"HappyDown", 55, 56, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"HappyRight", 57, 58, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"AllHandDown", 59, 59, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"RightHandDown", 60, 60, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"LeftHandDown", 61, 61, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"AllHandUp", 62, 62, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"LeftHandUp", 63, 63, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"RightHandUp", 64, 64, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"Fighting", 65, 69, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"SitFix", 70, 70, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"Sleep", 76, 76, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"PrayDown", 80, 81, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"PrayUp", 82, 83, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"PrayRight", 84, 85, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"FlyPrayDown", 86, 87, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"FlyPrayUp", 88, 89, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"FlyPrayRight", 90, 91, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"DamageDown", 92, 92, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"DamageUp", 93, 93, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"DamageRight", 94, 94, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"Down", 185, 185, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponReadyDown", 105, 107, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponIdleDown", 108, 110, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponReadyUp", 111, 112, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponIdleUp", 113, 116, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponReadyLeft", 117, 118, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"WeaponIdleLeft", 119, 122, DFS, true);
	AnimatorVector[LUCCA]->CreateAnimation(L"HitDown", 123, 124, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"CriticalDown", 123, 126, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"HitUp", 127, 128, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"CriticalUp", 127, 130, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"HitRight", 131, 132, DFS, false);
	AnimatorVector[LUCCA]->CreateAnimation(L"CriticalRight", 131, 134, DFS, false);
#pragma endregion
#pragma region MaruAnimation
	Renderer->SetImage(L"Maru.png");
	AnimatorVector[MARU]->CreateAnimation(L"IdleDown", 0, 2, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"IdleUp", 3, 3, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"IdleRight", 4, 6, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WalkDown", 7, 12, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WalkUp", 13, 18, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WalkRight", 19, 24, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"RunDown", 37, 38, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"RunUp", 39, 40, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"RunRight", 41, 42, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"NoDown", 43, 45, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"NoUp", 46, 48, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"NoRight", 49, 51, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"DamageDown", 52, 52, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"DamageRight", 53, 53, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"ThinkDown", 54, 54, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"ThinkUp", 55, 55, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"ThinkRight", 56, 56, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"StandUp", 57, 57, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"StandDown", 58, 58, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"StandRight", 59, 59, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"Climb", 60, 63, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"HappyDown", 64, 65, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"HappyRight", 66, 67, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"AllHandDown", 68, 68, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"RightHandDown", 69, 69, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"LeftHandDown", 70, 70, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"AllHandUp", 71, 71, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"LeftHandUp", 72, 72, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"RightHandUp", 73, 73, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"PrayDown", 95, 98, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"PrayUp", 99, 102, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"PrayRight", 103, 106, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"FlyPrayDown", 107, 108, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"FlyPrayUp", 109, 110, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"FlyPrayRight", 111, 112, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"CastingDown", 113, 114, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"CastingUp", 115, 116, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"CastingRight", 117, 118, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"Down", 185, 185, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponReadyDown", 130, 133, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponIdleDown", 134, 136, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponReadyUp", 137, 140, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponIdleUp", 141, 143, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponReadyLeft", 144, 147, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"WeaponIdleLeft", 148, 150, DFS, true);
	AnimatorVector[MARU]->CreateAnimation(L"HitDown", 150, 151, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"CriticalDown", 150, 151, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"HitUp", 152, 153, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"CriticalUp", 152, 153, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"HitRight", 154, 155, DFS, false);
	AnimatorVector[MARU]->CreateAnimation(L"CriticalRight", 154, 155, DFS, false);
#pragma endregion
#pragma region KaeruAnimation
	Renderer->SetImage(L"Kaeru.png");
	AnimatorVector[KAERU]->CreateAnimation(L"IdleDown", 0, 0, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"IdleUp", 7, 7, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"IdleRight", 21, 21, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WalkDown", 0, 6, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WalkUp", 7, 13, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WalkRight", 21, 27, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"RunDown", 74, 77, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"RunUp", 78, 81, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"RunRight", 86, 89, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"NoDown", 43, 44, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"NoUp", 45, 46, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"NoRight", 49, 50, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"SurpriseDown", 90, 90, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"SurpriseRight", 92, 92, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"Climb", 93, 96, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"ThinkDown", 70, 70, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"ThinkUp", 71, 71, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"ThinkRight", 73, 73, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"HappyDown", 64, 65, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"HappyRight", 68, 69, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"Fighting", 97, 98, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"CrouchDown", 73, 73, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"CrouchRight", 74, 74, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"PrayDown", 131, 132, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"PrayUp", 133, 134, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"PrayRight", 136, 137, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"FlyPrayDown", 91, 92, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"FlyPrayUp", 93, 94, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"FlyPrayRight", 95, 96, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"DamageDown", 103, 103, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"DamageUp", 104, 104, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"DamageRight", 105, 105, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"MerongDown", 106, 107, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"MerongDown", 110, 111, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"MerongDown", 112, 113, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"Down", 53, 53, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponReadyDown", 28, 30, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponIdleDown", 31, 31, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponReadyUp", 32, 34, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponIdleUp", 35, 35, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponReadyLeft", 40, 42, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"WeaponIdleLeft", 43, 43, DFS, true);
	AnimatorVector[KAERU]->CreateAnimation(L"HitDown", 139, 141, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"CriticalDown", 139, 141, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"HitUp", 142, 144, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"CriticalUp", 142, 144, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"HitRight", 148, 150, DFS, false);
	AnimatorVector[KAERU]->CreateAnimation(L"CriticalRight", 148, 150, DFS, false);
#pragma endregion
	//AnimatorVector[ROBO];
	//AnimatorVector[EIRA];
	//AnimatorVector[MAOU];
}

void NTPlayer::SetRenderChara(CHARACTER _Chara)
{
	Character = _Chara;

	switch (Character)
	{
	case CHRONO:
		Renderer->SetImage(L"Chrono.png");
		Animator = AnimatorVector[CHRONO];
		break;
	case LUCCA:
		Renderer->SetImage(L"Lucca.png");
		Animator = AnimatorVector[LUCCA];
		break;
	case MARU:
		Renderer->SetImage(L"Maru.png");
		Animator = AnimatorVector[MARU];
		break;
	case KAERU:
		Renderer->SetImage(L"Kaeru.png");
		Animator = AnimatorVector[KAERU];
		break;
	case ROBO:
	case EIRA:
	case MAOU:
	case CHARA_MAX:
	default:
		break;
	}
}


bool NTPlayer::Init()
{
	if (Renderer == nullptr)
	{
		Renderer = AddComponent<NTSpRenderer>();
	}
	if (Animator == nullptr)
	{
		Animator = AddComponent<NTSpFrameAnimator>();
	}
	Collider = AddComponent<NT2DCollision>(PlayerLayer);
	Collider->SetMode(COLTYPE::CT_2D_RECT);
	
	SetRendererDefaultData();
	GetNTObject()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	GetNTObject()->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });

	Renderer->SetSubScale({ 400.0f, 400.0f, 1.0f });
	Renderer->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Collider->SetRect({ 0.0f, -25.0f, 50.0f, 50.0f });
	Collider->EnterFunc<NTPlayer>(this, &NTPlayer::ColEnter);
	Collider->ExitFunc<NTPlayer>(this, &NTPlayer::ColExit);
	Collider->SetName(L"MainCollider");

	PixelCollider = AddComponent<NTPixelCollider>();

	BattleCom = AddComponent<NTBattle>(Status->Speed);

	return true;
}

bool NTPlayer::Init(CHARACTER _Chara)
{
	Renderer = AddComponent<NTSpRenderer>();
	Animator = AddComponent<NTSpFrameAnimator>();
	SetRendererDefaultData();
	Character = _Chara;
	Status = GameSystem::GetStatus(Character);
	Status->IsFront = false;
	SetRenderChara(Character);
	return Init();
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
float Tmp = 0.0f;
void NTPlayer::MainUpdate()
{
	if (bMove == true || bAttack == true)
	{
		MoveTo(MoveToVec, MoveSpeed);
	}


	if (GameSystem::GetBattlePhase() == true && bMove == false && Animator->IsAniEnd() == true)
	{
		BattleCom->Ready();
	}

	if (lstrcmpW(NextAni, L"HitUp") == 0 && Animator->IsAniEnd() == true)
	{
		ReturnToDefaultPos();
	}


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
				Animator->ChangeAnimationReverse(L"RunRight", true, false);
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
				Animator->ChangeAnimationReverse(L"WalkRight", true, false);
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
			Animator->ChangeAnimationReverse(L"WalkRight", true, false);
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

	if (Status->IsFront == false && GameSystem::GetBattlePhase() == false)
	{
		if (FrontPlayer == nullptr)
		{
			if (lstrcmpW(GetNTObject()->GetName(), L"Player02") == 0)
			{
				FrontPlayer = GetScene()->FindObject(L"Player01");
			}

			if (lstrcmpW(GetNTObject()->GetName(), L"Player03") == 0)
			{
				FrontPlayer = GetScene()->FindObject(L"Player02");
			}
		}

		float Dir = 0.0f;
		Dir = MathSystem::GetDistance(GetNTObject()->GetTransform()->GetLocalPosition(), FrontPlayer->GetTransform()->GetLocalPosition());

		float Deg;
		NTVEC Vec = FrontPlayer->GetTransform()->GetLocalPosition() - GetNTObject()->GetTransform()->GetLocalPosition();
		Deg = MathSystem::GetDegree2D(Vec, NTVEC(0.0f));
		Tmp = Deg;
		Vec.Normalize();
		if (Dir > 50.0f)
		{
			if (Deg >= 315.0f || Deg <= 45.0f)
			{
				if (PixelCollider->MoveColCheck(NTVEC::LEFT, TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove(Vec * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					Direction = PD_LEFT;
				}
				else
				{
					if (Deg > 0.0f && Deg < 315.0f)
					{
						GetNTObject()->GetTransform()->SetLocalMove(NTVEC::DOWN * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					}
					else
					{
						GetNTObject()->GetTransform()->SetLocalMove(NTVEC::UP * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					}
				}
				Animator->ChangeAnimationReverse(L"WalkRight", true, false);
			}

			if (Deg >= 45.0f && Deg <= 135.0f)
			{
				if (PixelCollider->MoveColCheck(NTVEC::DOWN, TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove(Vec * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					Direction = PD_DOWN;
				}
				Animator->ChangeAnimation(L"WalkDown");
			}

			if (Deg >= 135.0f && Deg <= 225.0f)
			{
				if (PixelCollider->MoveColCheck(NTVEC::RIGHT, TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove(Vec * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					Direction = PD_RIGHT;
				}
				Animator->ChangeAnimation(L"WalkRight");
			}

			if (Deg >= 225.0f && Deg <= 315.0f)
			{
				if (PixelCollider->MoveColCheck(NTVEC::UP, TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f) == true)
				{
					GetNTObject()->GetTransform()->SetLocalMove(Vec * TimeSystem::DeltaTime() * FieldSpeed * Dir * 0.01f);
					Direction = PD_UP;
				}
				Animator->ChangeAnimation(L"WalkUp");
			}
		}
		else
		{
			if (Deg >= 315.0f || Deg <= 45.0f)
			{
				Animator->ChangeAnimationReverse(L"IdleRight", true, false);
			}

			if (Deg >= 45.0f && Deg <= 135.0f)
			{
				Animator->ChangeAnimation(L"IdleDown");
			}

			if (Deg >= 135.0f && Deg <= 225.0f)
			{
				Animator->ChangeAnimation(L"IdleRight");
			}

			if (Deg >= 225.0f && Deg <= 315.0f)
			{
				Animator->ChangeAnimation(L"IdleUp");
			}
		}

	}
}


void NTPlayer::DbgRender()
{
	/*wchar_t TTTTT[32] = {};
	swprintf_s(TTTTT, L"%f", Tmp);
	DebugFunc::DrawFont(TTTTT, NTVEC2(0.0f), 50.0f, 0xffffffff);*/
}

void NTPlayer::SetFieldRenderer(Autoptr<NTSpRenderer> _Renderer)
{
	PixelCollider->SetSourceRenderer(_Renderer);
}

void NTPlayer::MoveTo(NTVEC _Value, float _Speed)
{
	NTVEC CurPos = GetNTObject()->GetTransform()->GetLocalPosition();
	NTVEC DirVec = _Value - CurPos;
	float Dist = MathSystem::GetDistance2D(_Value, CurPos);
	if (Dist > 10.0f)
	{
		DirVec.Normalize();
		GetNTObject()->GetTransform()->SetLocalMove(NTVEC2{ DirVec * TimeSystem::DeltaTime() * _Speed });
		
	}
	else
	{
		Animator->ChangeAnimation(NextAni);
		bMove = false;
		bAttack = false;
		return;
	}
}


Autoptr<NTSpFrameAnimator> NTPlayer::GetCurAnimator()
{
	return Animator;
}

float NTPlayer::AttackDamage()
{
	int f = rand() % 20;
	
	return (float)(Status->Power + 2) * (float)(100 - f) * (float)Status->Weapon.Atk;
}

float NTPlayer::AttackDefence()
{
	int c = rand() % 5 - 1;
	return (((float)(Status->Stamina + 2) * 400.0f) * 10.0f) / (20000.0f * ((float)c / 1000.0f));
}

float NTPlayer::TechDamage()
{
	return 0.0f;
}

float NTPlayer::TechDefence()
{
	return 0.0f;
}

float NTPlayer::ElementDamage()
{
	return 0.0f;
}

float NTPlayer::ElementDefence()
{
	return 0.0f;
}

void NTPlayer::ColEnter(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
}

void NTPlayer::ColExit(NTCollisionComponent * _Left, NTCollisionComponent * _Right)
{
}

