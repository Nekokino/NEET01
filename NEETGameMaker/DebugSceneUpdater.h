#pragma once
#include <NTScene.h>
#include <Windows.h>
#include <string>

class NTFadeRect;
class NTFontRenderer;
class NTPixelChecker;
class DebugSceneUpdater : public NTScene::NTSceneUpdater
{
private:
	wchar_t TextString[256];

	Autoptr<NTObject> Player;
	Autoptr<NTFontRenderer> FontRender;
	Autoptr<NTFadeRect> FadeRect;
	Autoptr<NTPixelChecker> PixelChecker;

	POINT MousePos;
public:
	DebugSceneUpdater();
	~DebugSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

