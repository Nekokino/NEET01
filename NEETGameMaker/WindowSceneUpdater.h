#pragma once
#include <NTScene.h>
class WindowSceneUpdater : public NTScene::NTSceneUpdater
{
public:
	WindowSceneUpdater();
	~WindowSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

