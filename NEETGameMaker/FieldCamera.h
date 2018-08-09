#pragma once

#include <NTLogic.h>

class NTCamera;
class NTTransform;
class NTField;
class FieldCamera : public NTLogic
{
private:
	Autoptr<NTCamera> Cam;
	Autoptr<NTTransform> FocusTrans;
	Autoptr<NTField> Field;

	NTRECT MoveRange;
public:
	bool Init();
	bool Init(Autoptr<NTCamera> _Cam);
	bool Init(Autoptr<NTCamera> _Cam, Autoptr<NTTransform> _Trans);
	bool Init(Autoptr<NTCamera> _Cam, Autoptr<NTTransform> _Trans, Autoptr<NTField> _Field);
	void MainUpdate() override;

	void SetCam(Autoptr<NTCamera> _Cam);
	void SetFocus(Autoptr<NTTransform> _Trans);
	void SetField(Autoptr<NTField> _Field);
public:
	FieldCamera();
	~FieldCamera();
};

