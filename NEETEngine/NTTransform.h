#pragma once
#include "MathSystem.h"
#include "NTComponent.h"
class NTTransform : public NTComponent
{
public:
	enum AXIS
	{
		AX_FORWARD,
		AX_UP,
		AX_RIGHT,
		AX_MAX,
	};

public:
	static bool IsMulti(NTObject* _Obj);

private:
	bool bLocalScale;
	bool bLocalRotation;
	bool bLocalPosition;
	bool bWorld;
	bool ForceUpdate;

	NTVEC LocalScale;
	NTVEC LocalRotation;
	NTVEC LocalPosition;

	NTVEC WorldScale;
	NTVEC WorldRotation;
	NTVEC WorldPosition;

	NTVEC LocalAxis[AXIS::AX_MAX];
	NTVEC WorldAxis[AXIS::AX_MAX];

	NTMAT ScaleMatrix;
	NTMAT RotationXMatrix, RotationYMatrix, RotationZMatrix;
	NTMAT RotationMatrix;
	NTMAT PositionMatrix;

	NTMAT WorldMatrix;

public:
	bool IsWorldUpdated() { return bWorld; }

	NTVEC GetLocalPosition() const
	{
		return LocalPosition;
	}

	NTVEC GetWorldPosition() const
	{
		return WorldPosition;
	}

	NTVEC GetLocalRotation() const
	{
		return LocalRotation;
	}

	NTVEC GetWorldRotation() const
	{
		return WorldRotation;
	}

	NTVEC GetLocalScale() const
	{
		return LocalScale;
	}

	NTVEC GetWorldScale() const
	{
		return WorldScale;
	}

	const NTVEC GetWorldScaleConst() const
	{
		return WorldScale;
	}

	void SetLocalPosition(const NTVEC& _Pos)
	{
		LocalPosition = _Pos;
		bLocalPosition = true;
		bWorld = true;
	}

	void SetWorldPosition(const NTVEC& _Pos)
	{
		WorldPosition = _Pos;
		bWorld = true;
	}

	void SetLocalMove(const NTVEC& _Value)
	{
		LocalPosition += _Value;
		bLocalPosition = true;
		bWorld = true;
	}

	void SetLocalRotation(const NTVEC& _Value)
	{
		LocalRotation = _Value;
		bLocalRotation = true;
		bWorld = true;
	}

	void SetLocalAccRotation(const NTVEC& _Value)
	{
		LocalRotation += _Value;
		bLocalRotation = true;
		bWorld = true;
	}

	void SetLocalScale(const NTVEC& _Scale)
	{
		LocalScale = _Scale;
		bLocalScale = true;
		bWorld = true;
	}


	NTVEC GetLocalForward() { return LocalAxis[AX_FORWARD]; }
	NTVEC GetWorldForward() { return LocalAxis[AX_FORWARD]; }
	NTVEC GetLocalUp() { return LocalAxis[AX_UP]; }
	NTVEC GetWorldUp() { return LocalAxis[AX_UP]; }
	NTVEC GetLocalRight() { return LocalAxis[AX_RIGHT]; }
	NTVEC GetWorldRight() { return LocalAxis[AX_RIGHT]; }
	NTVEC GetLocalBack() { return LocalAxis[AX_FORWARD] * -1.0f; }
	NTVEC GetWorldBack() { return LocalAxis[AX_FORWARD] * -1.0f; }
	NTVEC GetLocalDown() { return LocalAxis[AX_UP] * -1.0f; }
	NTVEC GetWorldDown() { return LocalAxis[AX_UP] * -1.0f; }
	NTVEC GetLocalLeft() { return LocalAxis[AX_RIGHT] * -1.0f; }
	NTVEC GetWorldLeft() { return LocalAxis[AX_RIGHT] * -1.0f; }

	NTMAT GetWorldMatrix() const
	{
		return WorldMatrix;
	}

	const NTMAT& GetWorldMatrixConst() const
	{
		return WorldMatrix;
	}

	void Reset();

	void ForceMove()
	{
		ForceUpdate = true;
	}

public:
	virtual bool Init() override;
	virtual void MainUpdate() override;
	virtual void FinalUpdate() override;
	virtual void EndUpdate() override;
public:
	NTTransform();
	~NTTransform();
};

