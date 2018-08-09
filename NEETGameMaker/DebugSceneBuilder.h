#pragma once
#include <NTScene.h>

class DebugSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	DebugSceneBuilder();
	~DebugSceneBuilder();

	virtual void SceneBuild() override;
};

