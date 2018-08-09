#pragma once
#include <NTScene.h>
#include <Windows.h>
class TitleSceneUpdater : public NTScene::NTSceneUpdater
{
public:
	TitleSceneUpdater();
	~TitleSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

