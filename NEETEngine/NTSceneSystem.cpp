#include "PreCom.h"
#include "NTSceneSystem.h"
#include "StlAssist.h"


NTSceneSystem::NTSceneSystem(NTWindow* _Window)
{
	SetNTWindow(_Window);
}


NTSceneSystem::~NTSceneSystem()
{
}

void NTSceneSystem::ChangeScene(const wchar_t* _Name)
{
	if (nullptr == _Name)
	{
		NextScene = nullptr;
	}

	NextScene = FindScene(_Name);
	tassert(nullptr == NextScene);
}

Autoptr<NTScene> NTSceneSystem::FindScene(const wchar_t* _Name)
{
	return MapFind<Autoptr<NTScene>>(SceneMap, _Name);
}

void NTSceneSystem::Progress()
{
	if (nullptr != NextScene)
	{
		CurScene = NextScene;
		NextScene = nullptr;
	}

	if (nullptr != CurScene && true == CurScene->IsUpdate())
	{
		CurScene->Progress();
	}
}

void NTSceneSystem::PreProgress()
{
	if (nullptr != CurScene && true == CurScene->IsUpdate())
	{
		CurScene->PreProgress();
	}
}

void NTSceneSystem::Render()
{
	if (nullptr != CurScene && true == CurScene->IsUpdate())
	{
		CurScene->Render();
		CurScene->DbgRender();
	}
}

void NTSceneSystem::Release()
{
	if (nullptr != CurScene && true == CurScene->IsUpdate())
	{
		CurScene->Release();
	}
}

Autoptr<NTScene> NTSceneSystem::CreateScene(const wchar_t* _Name)
{
	if (nullptr != FindScene(_Name))
	{
		return nullptr;
	}

	NTScene* NewScene = new NTScene();
	NewScene->SetSceneSystem(this);
	NewScene->SetName(_Name);
	NewScene->SetNTWindow(GetNTWindow());
	NewScene->SetType();

	SceneMap.insert(std::unordered_map<std::wstring, Autoptr<NTScene>>::value_type(_Name, NewScene));

	return NewScene;
}

void NTSceneSystem::OverCheck(NTScene * _Scene)
{
	std::list<Autoptr<NTObject>>::iterator StartIter = OverObjectList.begin();
	std::list<Autoptr<NTObject>>::iterator EndIter = OverObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (OST_ALL != (*StartIter)->GetOSType())
		{
			continue;
		}

		_Scene->PushOverObject(*StartIter);
	}
}

bool NTSceneSystem::FindOverObj(Autoptr<NTObject> _Obj)
{
	std::list<Autoptr<NTObject>>::iterator StartIter = OverObjectList.begin();
	std::list<Autoptr<NTObject>>::iterator EndIter = OverObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == _Obj)
		{
			return true;
		}
	}

	return false;
}