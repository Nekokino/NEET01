#include "LoadingSceneBuilder.h"
#include "NTField.h"
#include <NTSpFrameAnimator.h>
#include <NTSpRenderer.h>
#include <unordered_map>
#include <string>

LoadingSceneBuilder::LoadingSceneBuilder()
{
}


LoadingSceneBuilder::~LoadingSceneBuilder()
{
}

void LoadingSceneBuilder::SceneBuild()
{
	AllFieldLoad();	
	NTField::DefaultDataSet();
}

void LoadingSceneBuilder::AllFieldLoad()
{

}
