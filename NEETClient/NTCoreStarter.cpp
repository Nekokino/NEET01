#include "NTCoreStarter.h"
#include <memory>
#include <NTWindow.h>
#include <InputSystem.h>
#include <NTWinShortCut.h>
#include <ResourceSystem.h>
#include <NTImage.h>
#include <SpriteLoader.h>
#include <TextLoader.h>
#include <ItemLoader.h>

#include "TitleSceneBuilder.h"
#include "TitleSceneUpdater.h"
#include <LoadingSceneBuilder.h>
#include <LoadingSceneUpdater.h>
#include <DebugSceneBuilder.h>
#include <DebugSceneUpdater.h>
#include <WindowSceneBuilder.h>
#include <WindowSceneUpdater.h>
#include <GameSystem.h>

NTCoreStarter::NTCoreStarter()
{
}


NTCoreStarter::~NTCoreStarter()
{
}

void NTCoreStarter::Build()
{
	NTWinShortCut::GetMainWindow().SetSize(1024, 896);
	NTWinShortCut::GetMainWindow().Show();
	NTWinShortCut::GetMainWindow().InitDevice();

	PathSystem::CreateAllPath(L"Texture");
	
	SpriteLoader::Load();
	TextLoader::Load();
	ItemLoader::Load();

	GameSystem::BaseSetting();
	
	NTWinShortCut::GetMainSceneSystem().CreateScene<LoadingSceneBuilder, LoadingSceneUpdater>(L"LoadingScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<WindowSceneBuilder, WindowSceneUpdater>(L"WindowScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<DebugSceneBuilder, DebugSceneUpdater>(L"DebugScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<TitleSceneBuilder, TitleSceneUpdater>(L"TitleScene");	
	
	NTWinShortCut::GetMainSceneSystem().ChangeScene(L"DebugScene");

	InputSystem::CreateKey(L"ArrowUp", VK_UP);
	InputSystem::CreateKey(L"ArrowDown", VK_DOWN);
	InputSystem::CreateKey(L"ArrowLeft", VK_LEFT);
	InputSystem::CreateKey(L"ArrowRight", VK_RIGHT);

	InputSystem::CreateKey(L"Key1", 'A');
	InputSystem::CreateKey(L"Key2", 'S');

	InputSystem::CreateKey(L"TestKey", VK_LBUTTON);
	InputSystem::CreateKey(L"MouseL", VK_LBUTTON);
	InputSystem::CreateKey(L"MouseR", VK_RBUTTON);
}