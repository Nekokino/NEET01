#pragma once
#include <NTScene.h>
#include <Windows.h>

class OverWorldSceneUpdater : public NTScene::NTSceneUpdater
{
public:
	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
public:
	OverWorldSceneUpdater();
	~OverWorldSceneUpdater();
};

