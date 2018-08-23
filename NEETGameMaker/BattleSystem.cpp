#include "BattleSystem.h"

#include <NTCamera.h>
#include <NTScene.h>
#include <NTWinShortCut.h>

#include "FieldCamera.h"
#include "GameSystem.h"
#include "NTBattle.h"
#include "NTPixelChecker.h"
#include "NTPlayer.h"
#include "NTEnemy.h"

BattleSystem::BattleSystem() : SceneCamera(nullptr)
{
	BattlePlayerVector.reserve(3);
}


BattleSystem::~BattleSystem()
{
}

bool BattleSystem::Init()
{
	SceneCamera = GetScene()->FindObject(L"MainCamera", 0);

	return true;
}

void BattleSystem::MainUpdate()
{
}

void BattleSystem::AfterUpdate()
{
}

void BattleSystem::DbgRender()
{
}

void BattleSystem::SetPlayerPosition()
{
	size_t PlayerCount = BattlePlayerVector.size();
	NTVEC WinSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	if (PlayerCount == 1)
	{
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetMove({ 0.0f, -100.0f }, 500.0f);
	}

	if (PlayerCount == 2)
	{
		
	}

	if (PlayerCount == 3)
	{

	}
}

void BattleSystem::EnterBattle(std::list<Autoptr<NTObject>>* _EnemyList)
{
	SceneCamera->GetComponent<FieldCamera>()->SetUpdate(false);
	GameSystem::SetBattlePhase(true);

	BattleEnemyList = *_EnemyList;
	if (GetScene()->FindObject(L"Player01") != nullptr)
	{
		BattlePlayerVector.push_back(GetScene()->FindObject(L"Player01"));
	}

	if (GetScene()->FindObject(L"Player02") != nullptr)
	{
		BattlePlayerVector.push_back(GetScene()->FindObject(L"Player02"));
	}

	if (GetScene()->FindObject(L"Player03") != nullptr)
	{
		BattlePlayerVector.push_back(GetScene()->FindObject(L"Player03"));
	}

	//for (; ListStartIter != ListEndIter; ++ListStartIter)
	//{
	//	Autoptr<NTPixelChecker> TmpPointer = (*ListStartIter)->GetComponent<NTPixelChecker>();
	//	if (TmpPointer != nullptr)
	//	{
	//		TmpPointer->SetUpdate(false);
	//	}
	//}
	// 그냥 픽셀체커 업데이트에서 배틀중이면 안하게 해주자. 에휴..

	for (size_t i = 0; i < BattlePlayerVector.size(); i++)
	{
		if (BattlePlayerVector[i]->GetComponent<NTPixelChecker>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NTPixelChecker>()->SetUpdate(false);
		}
	}

	SetPlayerPosition();
}

void BattleSystem::EndBattle()
{
	SceneCamera->GetComponent<FieldCamera>()->SetUpdate(true);
	GameSystem::SetBattlePhase(false);


	//for (; ListStartIter != ListEndIter; ++ListStartIter)
	//{
	//	Autoptr<NTPixelChecker> TmpPointer = (*ListStartIter)->GetComponent<NTPixelChecker>();
	//	if (TmpPointer != nullptr)
	//	{
	//		TmpPointer->SetUpdate(true);
	//	}
	//}

	for (size_t i = 0; i < BattlePlayerVector.size(); i++)
	{
		if (BattlePlayerVector[i]->GetComponent<NTPixelChecker>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NTPixelChecker>()->SetUpdate(true);
		}
	}

	BattlePlayerVector.clear();
	BattleEnemyList.clear();
}