#pragma once
#include <NTScene.h>
class WindowSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	WindowSceneBuilder();
	~WindowSceneBuilder();

	virtual void SceneBuild() override;
};

