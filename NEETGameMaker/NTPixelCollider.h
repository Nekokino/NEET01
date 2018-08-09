#pragma once
#include <NTLogic.h>
#include <vector>

class NT2DCollision;
class NTPixelChecker;
class NTSpRenderer;
class NTPixelCollider : public NTLogic
{
private:
	Autoptr<NT2DCollision> Collider;
	Autoptr<NTPixelChecker> PixelChecker;
	std::vector<NTCOLOR> BorderColorInfo;
	NTCOLOR CenterColorInfo;

	bool FloorCheck(NTCOLOR _Left, NTCOLOR _Right);

public:
	bool Init();
	void SetSourceRenderer(Autoptr<NTSpRenderer> _Renderer);
	void MainUpdate() override;
	void DbgRender() override;

	NTCOLOR GetCenterColor()
	{
		return CenterColorInfo;
	}

	NTCOLOR GetBorderColor(int _index)
	{
		return BorderColorInfo[_index];
	}

	bool MoveColCheck(NTVEC _DirVec, float _Dis);
public:
	NTPixelCollider();
	~NTPixelCollider();
};

