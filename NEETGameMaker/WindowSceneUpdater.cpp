#include "WindowSceneUpdater.h"
#include "GameSystem.h"
#include "NTPieceWindow.h"

#include <InputSystem.h>


WindowSceneUpdater::WindowSceneUpdater()
{
}


WindowSceneUpdater::~WindowSceneUpdater()
{
}

void WindowSceneUpdater::SceneUpdate()
{
	GameSystem::TimeUpdate();
}

void WindowSceneUpdater::SceneStart()
{
}
