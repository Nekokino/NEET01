#pragma once
#include <NTScene.h>
class OverWorldSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	OverWorldSceneBuilder();
	~OverWorldSceneBuilder();

	virtual void SceneBuild() override;
};

