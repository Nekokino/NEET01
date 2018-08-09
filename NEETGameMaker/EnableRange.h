#pragma once

#include <NTLogic.h>

class NTField;
class EnableRange : public NTLogic
{
public:
	Autoptr<NTField> CurField;

public:
	bool Init(Autoptr<NTField> _Field);
	void FinalUpdate() override;
public:
	EnableRange();
	~EnableRange();
};

