#pragma once
#include <NTScene.h>

class TestSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	TestSceneBuilder();
	~TestSceneBuilder();

	virtual void SceneBuild() override;
};

