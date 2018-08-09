#pragma once
#include <NTScene.h>
#include <Windows.h>


class NTObject;
class NTSpRenderer;
class NTTextWindow;
class NTFontRenderer;
class NTFadeRect;
class TestSceneUpdater : public NTScene::NTSceneUpdater
{
public:
	Autoptr<NTObject> UICamera;
	Autoptr<NTObject> UIObj;
	Autoptr<NTTextWindow> TextWindow;
	Autoptr<NTFontRenderer> FontRender;
	Autoptr<NTFadeRect> FadeRect;
	Autoptr<NTFontRenderer> MouseDbgFont;

	POINT MousePos;

public:
	TestSceneUpdater();
	~TestSceneUpdater();

	virtual void SceneUpdate() override;
	virtual void SceneStart() override;
};

