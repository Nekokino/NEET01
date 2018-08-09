#pragma once
#include <NTScene.h>

// 모든것을 여기서 로딩한다.
// 게임 내내 들고있을 것들을 여기서 다 드는 과정을 넣는다.
class LoadingSceneBuilder : public NTScene::NTSceneBuilder
{
public:
	void AllFieldLoad();
public:
	LoadingSceneBuilder();
	~LoadingSceneBuilder();

	virtual void SceneBuild() override;
};

