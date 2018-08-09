#include "LoadingSceneUpdater.h"
#include <NTWinShortCut.h>



LoadingSceneUpdater::LoadingSceneUpdater()
{
}


LoadingSceneUpdater::~LoadingSceneUpdater()
{
}

void LoadingSceneUpdater::SceneUpdate()
{
	NTWinShortCut::GetMainSceneSystem().ChangeScene(L"TestScene");
}

void LoadingSceneUpdater::SceneStart()
{
	
}
