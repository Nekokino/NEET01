#pragma once
#include "NTResource.h"


class NTShader : public NTResource
{
public:
	enum STYPE
	{
		ST_NONE,
		ST_VS,
		ST_PX,
	};
protected:
	STYPE Type;
	ID3DBlob* Blob; // ���̴� �ڵ带 ������������ ������ ����Ʈ �迭
	ID3DBlob* ErrBlob; // ���� ����Ʈ �迭

public:
	STYPE GetSType()
	{
		return Type;
	}
private:
	virtual void Update() = 0;
public:
	NTShader();
	~NTShader();
};

