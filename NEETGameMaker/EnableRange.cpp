#include "EnableRange.h"
#include "NTField.h"
#include <NTSpRenderer.h>

bool EnableRange::Init(Autoptr<NTField> _Field)
{
	CurField = _Field;
	return true;
}

void EnableRange::FinalUpdate()
{
	if (CurField == nullptr)
	{
		return;
	}

	NTVEC CurPos = GetNTObject()->GetTransform()->GetLocalPosition();
	NTVEC2 FieldSize = CurField->GetFieldImage()->GetSubScale();

	if (CurPos.x > FieldSize.x * 0.5f)
	{
		GetNTObject()->GetTransform()->SetLocalMove({ FieldSize.x * 0.5f - CurPos.x, 0.0f, 0.0f });
	}

	if (CurPos.x < FieldSize.x * -0.5f)
	{
		GetNTObject()->GetTransform()->SetLocalMove({ -FieldSize.x * 0.5f - CurPos.x, 0.0f, 0.0f });
	}

	if (CurPos.y > FieldSize.y * 0.5f)
	{
		GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, FieldSize.y * 0.5f - CurPos.y, 0.0f });
	}

	if (CurPos.y < FieldSize.y * -0.5f)
	{
		GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, -FieldSize.y * 0.5f - CurPos.y, 0.0f });
	}
}

EnableRange::EnableRange() : CurField(nullptr)
{
}


EnableRange::~EnableRange()
{
}
