#pragma once
#include <NTScene.h>
class TitleSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	TitleSceneBuilder();
	~TitleSceneBuilder();

	virtual void SceneBuild() override;
};

