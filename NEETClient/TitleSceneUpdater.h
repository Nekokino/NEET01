#pragma once
#include <NTScene.h>
#include <Windows.h>

class NTSoundPlayer;
class TitleSceneUpdater : public NTScene::NTSceneUpdater
{
private:
	Autoptr<NTSoundPlayer> BGM;
public:
	TitleSceneUpdater();
	~TitleSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

