#pragma once
#include <NTScene.h>

// ������ ���⼭ �ε��Ѵ�.
// ���� ���� ������� �͵��� ���⼭ �� ��� ������ �ִ´�.
class LoadingSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	void AllFieldLoad();
public:
	LoadingSceneBuilder();
	~LoadingSceneBuilder();

	virtual void SceneBuild() override;
};

