#include "NTPixelCollider.h"
#include <NT2DCollision.h>
#include "NTPixelChecker.h"
#include <NTSpRenderer.h>
#include "GameSystem.h"
#include <DebugFunc.h>

NTPixelCollider::NTPixelCollider() : Collider(nullptr), CenterColorInfo(0.0f)
{
	BorderColorInfo.reserve(8);
	for (size_t i = 0; i < 8; i++)
	{
		BorderColorInfo.push_back(0.0f);
	}
}


NTPixelCollider::~NTPixelCollider()
{
}

bool NTPixelCollider::Init()
{
	Collider = GetNTObject()->GetComponent<NT2DCollision>();
	PixelChecker = GetNTObject()->AddComponent<NTPixelChecker>();

	if (Collider == nullptr)
	{
		return false;
	}

	return true;
}

void NTPixelCollider::SetSourceRenderer(Autoptr<NTSpRenderer> _Renderer)
{
	PixelChecker->SetRenderer(_Renderer);
}

NTVEC aaaa = {};
void NTPixelCollider::MainUpdate()
{
	NTRECT ColliderRect = Collider->GetColliderVec();

	float Left = ColliderRect.Pos.x - ColliderRect.Size.x * 0.5f;
	float Right = ColliderRect.Pos.x + ColliderRect.Size.x * 0.5f;
	float Top = ColliderRect.Pos.y + ColliderRect.Size.x * 0.5f;
	float Bottom = ColliderRect.Pos.y - ColliderRect.Size.x * 0.5f;

	BorderColorInfo[0] = PixelChecker->GetPixelColor({ Left, Top });
	BorderColorInfo[1] = PixelChecker->GetPixelColor({ ColliderRect.Pos.x, Top });
	BorderColorInfo[2] = PixelChecker->GetPixelColor({ Right, Top });
	BorderColorInfo[3] = PixelChecker->GetPixelColor({ Left, ColliderRect.Pos.y });
	BorderColorInfo[4] = PixelChecker->GetPixelColor({ Right, ColliderRect.Pos.y });
	BorderColorInfo[5] = PixelChecker->GetPixelColor({ Left, Bottom });
	BorderColorInfo[6] = PixelChecker->GetPixelColor({ ColliderRect.Pos.x, Bottom });
	BorderColorInfo[7] = PixelChecker->GetPixelColor({ Right, Bottom });
	CenterColorInfo = PixelChecker->GetPixelColor(ColliderRect.Pos);

}

void NTPixelCollider::DbgRender()
{
	wchar_t ASD[256];
	swprintf_s(ASD, 256, L"%f, %f", aaaa.x, aaaa.y);
	DebugFunc::DrawFont(ASD, { 0.0f, 50.0f }, 50.0f, 0xffffffff);
}
bool NTPixelCollider::MoveColCheck(NTVEC _DirVec, float _Dis)
{
	NTVEC ColliderRect = Collider->GetColliderVec();
	NTVEC Move = _DirVec *_Dis;
	NTVEC Tmp = {};
	NTCOLOR Col = {};

	float Left = ColliderRect.Pos.x - ColliderRect.Size.x * 0.5f;
	float Right = ColliderRect.Pos.x + ColliderRect.Size.x * 0.5f;
	float Top = ColliderRect.Pos.y + ColliderRect.Size.x * 0.5f;
	float Bottom = ColliderRect.Pos.y - ColliderRect.Size.x * 0.5f;

	aaaa = NTVEC{ Left, Top };

	if (_DirVec == NTVEC::UP)
	{
		Tmp = NTVEC{ Left, Top };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ ColliderRect.Pos.x , Top };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Right, Top };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);

		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		return true;
	}

	if (_DirVec == NTVEC::DOWN)
	{
		Tmp = NTVEC{ Left, Bottom };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ ColliderRect.Pos.x , Bottom };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Right, Bottom };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);

		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		return true;
	}

	if (_DirVec == NTVEC::RIGHT)
	{
		Tmp = NTVEC{ Right, Top };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Right , ColliderRect.Pos.y };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Right, Bottom };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);

		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		return true;
	}

	if (_DirVec == NTVEC::LEFT)
	{
		Tmp = NTVEC{ Left, Top };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Left , ColliderRect.Pos.y };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);
		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		Tmp = NTVEC{ Left, Bottom };
		Tmp += Move;
		Col = PixelChecker->GetPixelColor(Tmp);

		if (FloorCheck(CenterColorInfo, Col) == true)
		{
			return false;
		}

		return true;
	}

	return false;
}

bool NTPixelCollider::FloorCheck(NTCOLOR _Left, NTCOLOR _Right)
{
	if (_Right == NTVEC{ 0.0f, 0.0f, 0.0f, 255.0f })
	{
		return true;
	}

	if (_Left == _Right)
	{
		return false;
	}

	
	if (_Left == Floor1)
	{
		if (_Right == Stair1)
		{
			return false;
		}
		return true;
	}

	if (_Left == Stair1)
	{
		if (_Right == Floor1 || _Right == Floor2)
		{
			return false;
		}

		return true;
	}

	if (_Left == Floor2)
	{
		if (_Right == Stair1 || _Right == Stair2)
		{
			return false;
		}

		return true;
	}

	if (_Left == Stair2)
	{
		if (_Right == Floor2 || _Right == Floor3)
		{
			return false;
		}

		return true;
	}

	if (_Left == Floor3)
	{
		if (_Right == Stair2 || _Right == Stair3)
		{
			return false;
		}

		return true;
	}

	if (_Left == Stair3)
	{
		if (_Right == Floor3 || _Right == Floor4)
		{
			return false;
		}

		return true;
	}

	if (_Left == Floor4)
	{
		if (_Right == Stair3 || _Right == Stair4)
		{
			return false;
		}

		return true;
	}

	if (_Left == Stair4)
	{
		if (_Right == Floor4 || _Right == Floor5)
		{
			return false;
		}

		return true;
	}

	if (_Left == Floor5)
	{
		if (_Right == Stair4)
		{
			return false;
		}

		return true;
	}

	return false;
}