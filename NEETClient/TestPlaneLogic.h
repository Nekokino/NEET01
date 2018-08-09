#pragma once
#include <NTLogic.h>
#include <NTCollisionComponent.h>

class NTSpRenderer;
class NTSpFrameAnimator;
class NT2DCollision;
class TestPlaneLogic : public NTLogic
{
private:
	size_t ImgIndex;
	
	Autoptr<NTSpRenderer> ChRenderer;
	Autoptr<NTSpRenderer> ChRenderer2;
	Autoptr<NTSpFrameAnimator> Animator;
	Autoptr<NT2DCollision> Collider;
public:
	bool Init() override;
	void MainUpdate() override;
	void DbgRender() override;

public:
	void ColEnter(NTCollisionComponent* _Left, NTCollisionComponent* _Right);
	void ColExit(NTCollisionComponent* _Left, NTCollisionComponent* _Right);

public:
	TestPlaneLogic();
	~TestPlaneLogic();
};

