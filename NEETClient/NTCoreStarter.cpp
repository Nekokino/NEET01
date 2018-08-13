#include "NTCoreStarter.h"
#include <memory>
#include <NTWindow.h>
#include <InputSystem.h>
#include <NTWinShortCut.h>
#include <ResourceSystem.h>
#include <NTImage.h>
#include <SpriteLoader.h>
#include <TextLoader.h>

#include "TestSceneUpdater.h"
#include "TestSceneBuilder.h"
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
	NTWinShortCut::GetMainWindow().SetSize(1024 * 0.75f, 896 * 0.75f);
	NTWinShortCut::GetMainWindow().Show();
	NTWinShortCut::GetMainWindow().InitDevice();

	PathSystem::CreateAllPath(L"Texture");
	
	SpriteLoader::Load();
	TextLoader::Load();

	GameSystem::BasePlayerSetting();
	
	NTWinShortCut::GetMainSceneSystem().CreateScene<LoadingSceneBuilder, LoadingSceneUpdater>(L"LoadingScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<WindowSceneBuilder, WindowSceneUpdater>(L"WindowScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<DebugSceneBuilder, DebugSceneUpdater>(L"DebugScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<TestSceneBuilder, TestSceneUpdater>(L"TestScene");
	NTWinShortCut::GetMainSceneSystem().CreateScene<TitleSceneBuilder, TitleSceneUpdater>(L"TitleScene");	
	
	NTWinShortCut::GetMainSceneSystem().ChangeScene(L"WindowScene");

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