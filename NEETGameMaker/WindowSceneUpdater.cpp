#include "WindowSceneUpdater.h"
#include "GameSystem.h"
#include "NTPieceWindow.h"

#include <InputSystem.h>
#include <NTWinShortCut.h>


WindowSceneUpdater::WindowSceneUpdater()
{
}


WindowSceneUpdater::~WindowSceneUpdater()
{
}

void WindowSceneUpdater::SceneUpdate()
{
	GameSystem::TimeUpdate();

	if (InputSystem::IsDown(L"Key3") == true)
	{
		NTWinShortCut::GetMainSceneSystem().ChangeScene(L"DebugScene");
	}
}

void WindowSceneUpdater::SceneStart()
{
}
