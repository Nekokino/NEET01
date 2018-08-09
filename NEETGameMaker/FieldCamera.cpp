#include "FieldCamera.h"

#include <NTCamera.h>
#include <NTTransform.h>
#include "NTField.h"
#include <NTSpRenderer.h>

FieldCamera::FieldCamera() : Cam(nullptr), MoveRange(0.0f), FocusTrans(nullptr), Field(nullptr)
{

}


FieldCamera::~FieldCamera()
{
}

bool FieldCamera::Init()
{
	Cam = nullptr;
	return true;
}

bool FieldCamera::Init(Autoptr<NTCamera> _Cam)
{
	SetCam(_Cam);
	return true;
}

bool FieldCamera::Init(Autoptr<NTCamera> _Cam, Autoptr<NTTransform> _Trans)
{
	SetCam(_Cam);
	SetFocus(_Trans);
	return true;
}

bool FieldCamera::Init(Autoptr<NTCamera> _Cam, Autoptr<NTTransform> _Trans, Autoptr<NTField> _Field)
{
	SetCam(_Cam);
	SetFocus(_Trans);
	SetField(_Field);
	return true;
}

void FieldCamera::MainUpdate()
{
	if (Cam == nullptr || FocusTrans == nullptr || Field == nullptr)
	{
		return;
	}

	MoveRange.Pos = Cam->GetNTObject()->GetTransform()->GetLocalPosition().Pos;
	MoveRange.Size = Cam->GetScreenSize().Pos / 2.0f;

	NTVEC Pos = FocusTrans->GetLocalPosition();
	NTRECT FieldScale = 0.0f;
	FieldScale.Pos = 0.0f;
	FieldScale.Size = Field->GetFieldImage()->GetSubScale().Pos;

	if (Pos.x < MoveRange.Left())
	{
		if (Pos.x - Cam->GetScreenSize().x / 4.0f > FieldScale.Left())
			Cam->GetNTObject()->GetTransform()->SetLocalMove({ Pos.x - MoveRange.Left(), 0.0f, 0.0f });
	}

	if (Pos.x > MoveRange.Right())
	{
		if (Pos.x + Cam->GetScreenSize().x / 4.0f < FieldScale.Right())
			Cam->GetNTObject()->GetTransform()->SetLocalMove({ Pos.x - MoveRange.Right(), 0.0f, 0.0f });
	}

	if (Pos.y < MoveRange.Bottom())
	{
		if (Pos.y - Cam->GetScreenSize().y / 4.0f > FieldScale.Bottom())
			Cam->GetNTObject()->GetTransform()->SetLocalMove({ 0.0f,  Pos.y - MoveRange.Bottom(), 0.0f });
	}

	if (Pos.y > MoveRange.Top())
	{
		if (Pos.y + Cam->GetScreenSize().y / 4.0f < FieldScale.Top())
			Cam->GetNTObject()->GetTransform()->SetLocalMove({ 0.0f,  Pos.y - MoveRange.Top(), 0.0f });
	}
}

void FieldCamera::SetCam(Autoptr<NTCamera> _Cam)
{
	Cam = _Cam;
	
}

void FieldCamera::SetFocus(Autoptr<NTTransform> _Trans)
{
	FocusTrans = _Trans;
}

void FieldCamera::SetField(Autoptr<NTField> _Field)
{
	Field = _Field;
}
