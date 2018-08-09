#pragma once
#include <NTScene.h>
class LoadingSceneUpdater : public NTScene::NTSceneUpdater
{
public:
	LoadingSceneUpdater();
	~LoadingSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

