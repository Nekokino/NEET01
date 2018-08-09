#include "PreCom.h"
#include "NTRenderer.h"
#include "ResourceSystem.h"
#include "NTScene.h"


NTRenderer::NTRenderer()
{
}


NTRenderer::~NTRenderer()
{
}

bool NTRenderer::Init(int _Order)
{
	Order = _Order;
	GetScene()->RenderSystem.PushRenderer(this, _Order);
	return true;
}

bool NTRenderer::SetMesh(const wchar_t* _Mesh)
{
	Mesh = ResourceSystem<NTMesh>::Find(_Mesh);
	tassert(nullptr == Mesh);

	if (nullptr == Mesh)
	{
		return false;
	}

	return true;
}

bool NTRenderer::SetMaterial(const wchar_t* _Material)
{
	Material = ResourceSystem<NTMaterial>::Find(_Material);
	tassert(nullptr == Material);

	if (nullptr == Material)
	{
		return false;
	}

	return true;
}