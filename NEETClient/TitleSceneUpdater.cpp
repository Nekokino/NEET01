#include "TitleSceneUpdater.h"

#include <InputSystem.h>
#include <NTWinShortCut.h>

#include <NTSoundPlayer.h>


TitleSceneUpdater::TitleSceneUpdater()
{
}


TitleSceneUpdater::~TitleSceneUpdater()
{
}

void TitleSceneUpdater::SceneUpdate()
{
	if (BGM->IsPlay() == false)
	{
		BGM->SoundPlay(L"Title.wav");
	}
	if (InputSystem::IsDown(L"Key1"))
	{
		BGM->StopSound();
		NTWinShortCut::GetMainSceneSystem().ChangeScene(L"DebugScene");
	}
}

void TitleSceneUpdater::SceneStart()
{
	Autoptr<NTObject> SoundObj = GetScene()->CreateObject(L"TMP", 0);
	BGM = SoundObj->AddComponent<NTSoundPlayer>();
}
