#pragma once

#include <NTLogic.h>
#include <vector>
#include "GameSystem.h"

class NTSpRenderer;
class NT2DCollision;
class NTCollisionComponent;
class NTSpFrameAnimator;
class NTPixelCollider;
class NTBattle;
class NTPlayer : public NTLogic
{
public:
	enum PLAYERDIRECTION
	{
		PD_DOWN,
		PD_LEFT,
		PD_UP,
		PD_RIGHT,
		PD_NONE,
	};
private:
	Autoptr<NTSpRenderer> Renderer;
	Autoptr<NT2DCollision> Collider;
	Autoptr<NT2DCollision> EventCollider;
	Autoptr<NTSpFrameAnimator> Animator;
	Autoptr<NTPixelCollider> PixelCollider;
	Autoptr<NTBattle> BattleCom;
	Autoptr<NTObject> FrontPlayer;
	PlayerStatus* Status;
	CHARACTER Character;
	PLAYERDIRECTION Direction;

	std::vector<Autoptr<NTSpFrameAnimator>> AnimatorVector;

	float FieldSpeed;
	NTVEC MoveToVec;
	NTVEC BattlePos;
	float MoveSpeed;
	bool bMove;
	bool bAttack;
	bool bReturn;
	bool DefaultSet;
	const wchar_t* NextAni;
private:
	void MoveTo(NTVEC _Value, float _Speed);
	void SetRendererDefaultData();
	void ReturnToDefaultPos()
	{
		NTVEC NormVec = BattlePos - GetNTObject()->GetTransform()->GetLocalPosition();
		NormVec.Normalize();
		if (MathSystem::GetDistance2D(BattlePos, GetNTObject()->GetTransform()->GetLocalPosition()) < 10.0f)
		{
			return;
		}
		GetNTObject()->GetTransform()->SetLocalMove({ NormVec, 0.0f });
	}
public:
	bool Init();
	bool Init(CHARACTER _Chara);
	void PreUpdate() override;
	void MainUpdate() override;
	void DbgRender() override;

	void SetFieldRenderer(Autoptr<NTSpRenderer> _Renderer);
	void SetMove(NTVEC _Value, float _Speed, const wchar_t* _AfterAni)
	{
		bMove = true;
		MoveToVec = _Value;
		MoveSpeed = _Speed;
		NextAni = _AfterAni;
	}

	void SetAttack(NTVEC _Value, float _Speed, const wchar_t* _AfterAni)
	{
		bAttack = true;
		MoveToVec = _Value;
		MoveSpeed = _Speed;
		NextAni = _AfterAni;
	}

	PlayerStatus* GetStatus()
	{
		return Status;
	}

	void SetRenderChara(CHARACTER _Chara);
	void SetFront()
	{
		Status->IsFront = true;
	}
	Autoptr<NTSpFrameAnimator> GetCurAnimator();

	void SetBattlePos(NTVEC _Value)
	{
		BattlePos = _Value;
	}

	float AttackDamage();
	float AttackDefence();
	float TechDamage();
	float TechDefence();
	float ElementDamage();
	float ElementDefence();

public:
	void ColEnter(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColExit(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
public:
	NTPlayer();
	~NTPlayer();
};

