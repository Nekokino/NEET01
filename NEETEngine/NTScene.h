#pragma once
#include "NTSwitcher.h"
#include "NTWinParent.h"
#include "NTSceneParent.h"
#include "NTRenderSystem.h"
#include "NT2DCollisionSystem.h"

#include <unordered_map>
#include <list>

class NTObject;
class NTSceneSystem;
class NTCamera;
class NTScene final : public NTSwitcher, public NTWinParent
{
private:
	friend NTSceneSystem;
	friend NTObject;
	friend NTCamera;

#pragma region Builder & Updater
public:
	class NTSceneUpdater : public RefCounter, public NTSceneParent, public NTWinParent, public NTTypeParent
	{
	public:
		friend NTScene;

	public:
		virtual void SceneStart() = 0;
		virtual void SceneUpdate() = 0;

	protected:
		NTSceneUpdater() {}
		~NTSceneUpdater() {}
	};

	class NTSceneBuilder : public RefCounter, public NTSceneParent, public NTWinParent, public NTTypeParent
	{
	public:
		friend NTScene;

	private:
		bool bBuild;

	public:
		virtual void SceneBuild() = 0;

	protected:
		NTSceneBuilder() : bBuild(false) {}
		~NTSceneBuilder() {}
	};

private:
	Autoptr<NTSceneBuilder> SceneBuilder;
	Autoptr<NTSceneUpdater> SceneUpdater;

public:
	template<typename T>
	Autoptr<T> GetBuilder()
	{
		return SceneBuilder;
	}

	template<typename T>
	Autoptr<T> GetUpdater()
	{
		return SceneUpdater;
	}

private:
	template<typename T>
	void CreateBuilder()
	{
		if (nullptr != SceneBuilder)
		{
			SceneBuilder = nullptr;
		}

		SceneBuilder = new T();
		SceneBuilder->SetScene(this);
		SceneBuilder->SetNTWindow(GetNTWindow());
		SceneBuilder->SetType();
	}

	template<typename T>
	void CreateUpdater()
	{
		if (nullptr != SceneUpdater)
		{
			SceneUpdater = nullptr;
		}

		SceneUpdater = new T();
		SceneUpdater->SetScene(this);
		SceneUpdater->SetNTWindow(GetNTWindow());
		SceneUpdater->SetType();
	}
#pragma endregion

public:
	void Build();

private:
	std::unordered_map<int, std::list<Autoptr<NTObject>>> ObjectMap;

	std::unordered_map<int, std::list<Autoptr<NTObject>>>::iterator MapStartIter;
	std::unordered_map<int, std::list<Autoptr<NTObject>>>::iterator MapEndIter;

	std::list<Autoptr<NTObject>>::iterator ListStartIter;
	std::list<Autoptr<NTObject>>::iterator ListEndIter;

private:
	void Progress();
	void PreUpdate();
	void MainUpdate();
	void AfterUpdate();
	void DbgUpdate();

	void FinalUpdate();
	void PreProgress();
	void EndUpdate();

private:
	void Render();
	void DbgRender();
	void Release();

public:
	Autoptr<NTObject> CreateObject(const wchar_t* _Name, int _Order);
	Autoptr<NTObject> FindObject(const wchar_t* _Name, int _Order);

private:
	NTCamera* MainCamera;

public:
	NTCamera* GetMainCamera();

public:
	NTRenderSystem RenderSystem;

public:
	NT2DCollisionSystem _2DCollsionSystem;

public:
	NTSceneSystem* SceneSystem;

	NTSceneSystem* GetSceneSystem()
	{
		return SceneSystem;
	}

private:
	void SetSceneSystem(NTSceneSystem* _System)
	{
		SceneSystem = _System;
	}


private:
	void MoveObject(Autoptr<NTObject> _Obj);
	bool EraseObject(Autoptr<NTObject> _Obj);

	void PushOverObject(NTObject* _Obj);
public:
	NTScene();
	~NTScene();
};

