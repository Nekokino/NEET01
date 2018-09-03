#pragma once
#include <NTScene.h>
#include <Windows.h>
#include <string>
#include <list>

class NTFadeRect;
class NTFontRenderer;
class NTPixelChecker;
class NTSoundPlayer;
class DebugSceneUpdater : public NTScene::NTSceneUpdater
{
private:
	wchar_t TextString[256];

	Autoptr<NTObject> Player;
	Autoptr<NTFontRenderer> FontRender;
	Autoptr<NTFadeRect> FadeRect;
	Autoptr<NTPixelChecker> PixelChecker;
	Autoptr<NTSoundPlayer> SoundPlayer;

	std::list<Autoptr<NTObject>> SceneEnemyList;

	POINT MousePos;

public:
	std::list<Autoptr<NTObject>>* GetEnemyList()
	{
		return &SceneEnemyList;
	}

	void AddEnemyList(Autoptr<NTObject> _Obj)
	{
		SceneEnemyList.push_back(_Obj);
	}
public:
	DebugSceneUpdater();
	~DebugSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

