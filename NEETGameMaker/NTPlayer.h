#pragma once

#include <NTLogic.h>
#include "GameSystem.h"

class NTSpRenderer;
class NT2DCollision;
class NTCollisionComponent;
class NTSpFrameAnimator;
class NTPixelCollider;
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
	PlayerStatus* Status;
	CHARACTER Character;
	PLAYERDIRECTION Direction;

	float FieldSpeed;
public:
	bool Init(CHARACTER _Chara);
	void PreUpdate() override;
	void MainUpdate() override;
	void DbgRender() override;

	void SetFieldRenderer(Autoptr<NTSpRenderer> _Renderer);
public:
	void ColEnter(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColExit(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
public:
	NTPlayer();
	~NTPlayer();
};

