#include "BattleSystem.h"

#include <NTCamera.h>
#include <NTScene.h>
#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>
#include <NT2DCollision.h>
#include <NTSpFrameAnimator.h>
#include <InputSystem.h>
#include <NTSoundPlayer.h>

#include "FieldCamera.h"
#include "GameSystem.h"
#include "NTBattle.h"
#include "NTPixelChecker.h"
#include "NTPlayer.h"
#include "NTEnemy.h"
#include "NTPieceWindow.h"
#include "NTTurnBar.h"

BattleSystem::BattleSystem() : SceneCamera(nullptr), CurStatus(BWS_MAX), bCursor(false), CurPlayerIndex(0), TurnReady(false), CurOrderIndex(0), CurEnemyIndex(0)
{
	BattlePlayerVector.reserve(3);
}


BattleSystem::~BattleSystem()
{
}

bool BattleSystem::Init()
{
	WinSize = NTVEC{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	SceneCamera = GetScene()->FindObject(L"MainCamera", 0);
	EnemyListObj = GetScene()->CreateObject(L"EnemyListObject", UILayer);
	EnemyListWindow = EnemyListObj->AddComponent<NTPieceWindow>(7, 3, 0.5f);
	EnemyListObj->GetTransform()->SetLocalPosition({ WinSize.x * -0.265f, WinSize.y * -0.375f, 5.0f });

	EnemyList01 = EnemyListObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EnemyList01->SetColor(255, 255, 255, 255);
	EnemyList01->SetSubPivot({ WinSize.x * -0.2f, WinSize.y * 0.1f, 0.0f });
	EnemyList01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EnemyList01->SetSize(30.0f);
	EnemyList01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EnemyList01->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	EnemyList02 = EnemyListObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EnemyList02->SetColor(255, 255, 255, 255);
	EnemyList02->SetSubPivot({ WinSize.x * -0.2f, WinSize.y * 0.05f, 0.0f });
	EnemyList02->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EnemyList02->SetSize(30.0f);
	EnemyList02->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EnemyList02->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	EnemyList03 = EnemyListObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EnemyList03->SetColor(255, 255, 255, 255);
	EnemyList03->SetSubPivot({ WinSize.x * -0.2f, WinSize.y * 0.0f, 0.0f });
	EnemyList03->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EnemyList03->SetSize(30.0f);
	EnemyList03->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EnemyList03->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	EnemyList04 = EnemyListObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EnemyList04->SetColor(255, 255, 255, 255);
	EnemyList04->SetSubPivot({ WinSize.x * -0.2f, WinSize.y * -0.05f, 0.0f });
	EnemyList04->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EnemyList04->SetSize(30.0f);
	EnemyList04->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EnemyList04->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	EnemyList01->HideFont();
	EnemyList02->HideFont();
	EnemyList03->HideFont();
	EnemyList04->HideFont();
	EnemyListWindow->HideWindow();

	PlayerStatusObj = GetScene()->CreateObject(L"PlayerStatusObject", UILayer);
	PlayerStatusWindow = PlayerStatusObj->AddComponent<NTPieceWindow>(9, 3, 0.5f);
	PlayerStatusObj->GetTransform()->SetLocalPosition({WinSize.x * 0.205f, WinSize.y * -0.375f, 5.0f});
	Player01Name = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player01Name->SetColor(255, 255, 255, 255);
	Player01Name->SetSubPivot({ WinSize.x * - 0.275f, WinSize.y * 0.075f, 0.0f });
	Player01Name->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player01Name->SetSize(30.0f);
	Player01Name->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player01Name->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player01HP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player01HP->SetColor(255, 255, 255, 255);
	Player01HP->SetSubPivot({ 0.0f, WinSize.y * 0.075f, 0.0f });
	Player01HP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player01HP->SetSize(30.0f);
	Player01HP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player01HP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player01MP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player01MP->SetColor(255, 255, 255, 255);
	Player01MP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.075f, 0.0f });
	Player01MP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player01MP->SetSize(30.0f);
	Player01MP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player01MP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player01TurnBar = GetScene()->CreateObject(L"TurnBar01", UILayer);
	PlayerStatusObj->AddChild(Player01TurnBar);
	Player01TurnBar->AddComponent<NTTurnBar>(UILayer);
	Player01TurnBar->GetTransform()->SetLocalPosition({ WinSize.x * 0.225f, WinSize.y * 0.05f, 0.0f });
	Player01Name->HideFont();
	Player01HP->HideFont();
	Player01MP->HideFont();
	Player01TurnBar->GetComponent<NTTurnBar>()->HideBar();

	Player02Name = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player02Name->SetColor(255, 255, 255, 255);
	Player02Name->SetSubPivot({ WinSize.x * -0.275f, WinSize.y * 0.025f, 0.0f });
	Player02Name->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player02Name->SetSize(30.0f);
	Player02Name->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player02Name->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player02HP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player02HP->SetColor(255, 255, 255, 255);
	Player02HP->SetSubPivot({ 0.0f, WinSize.y * 0.025f, 0.0f });
	Player02HP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player02HP->SetSize(30.0f);
	Player02HP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player02HP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player02MP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player02MP->SetColor(255, 255, 255, 255);
	Player02MP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.025f, 0.0f });
	Player02MP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player02MP->SetSize(30.0f);
	Player02MP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player02MP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player02TurnBar = GetScene()->CreateObject(L"TurnBar01", UILayer);
	PlayerStatusObj->AddChild(Player02TurnBar);
	Player02TurnBar->AddComponent<NTTurnBar>(UILayer);
	Player02TurnBar->GetTransform()->SetLocalPosition({ WinSize.x * 0.225f, WinSize.y * 0.0f, 0.0f });
	Player02TurnBar->GetComponent<NTTurnBar>()->HideBar();
	Player02Name->HideFont();
	Player02HP->HideFont();
	Player02MP->HideFont();

	Player03Name = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player03Name->SetColor(255, 255, 255, 255);
	Player03Name->SetSubPivot({ WinSize.x * -0.275f, WinSize.y *  -0.025f, 0.0f });
	Player03Name->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player03Name->SetSize(30.0f);
	Player03Name->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player03Name->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player03HP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player03HP->SetColor(255, 255, 255, 255);
	Player03HP->SetSubPivot({ 0.0f, WinSize.y * -0.025f, 0.0f });
	Player03HP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player03HP->SetSize(30.0f);
	Player03HP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player03HP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player03MP = PlayerStatusWindow->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Player03MP->SetColor(255, 255, 255, 255);
	Player03MP->SetSubPivot({ WinSize.x * 0.1f, WinSize.y *  -0.025f, 0.0f });
	Player03MP->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Player03MP->SetSize(30.0f);
	Player03MP->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Player03MP->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Player03TurnBar = GetScene()->CreateObject(L"TurnBar01", UILayer);
	PlayerStatusObj->AddChild(Player03TurnBar);
	Player03TurnBar->AddComponent<NTTurnBar>(UILayer);
	Player03TurnBar->GetTransform()->SetLocalPosition({ WinSize.x * 0.225f, WinSize.y * -0.05f, 0.0f });
	Player03TurnBar->GetComponent<NTTurnBar>()->HideBar();
	Player03Name->HideFont();
	Player03HP->HideFont();
	Player03MP->HideFont();
	
	PlayerStatusWindow->HideWindow();
	PlayerOrderObj = GetScene()->CreateObject(L"PlayerOrderObject", UILayer);
	PlayerOrderWindow = PlayerOrderObj->AddComponent<NTPieceWindow>(3, 3, 0.5f);
	PlayerOrderObj->GetTransform()->SetLocalPosition({ WinSize.x * -0.35f, WinSize.y * -0.375f, 5.0f});
	AttackString = PlayerOrderObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	AttackString->SetColor(255, 255, 255, 255);
	AttackString->SetSubPivot({ WinSize.x * -0.075f, WinSize.y * 0.09f, 0.0f });
	AttackString->SetSubScale({ 1.0f, 1.0f, 1.0f });
	AttackString->SetSize(30.0f);
	AttackString->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	AttackString->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	AttackString->SetString(L"°ø°Ý À§Ä¡");
	SkillString = PlayerOrderObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	SkillString->SetColor(255, 255, 255, 255);
	SkillString->SetSubPivot({ WinSize.x * -0.075f, WinSize.y * 0.03f, 0.0f });
	SkillString->SetSubScale({ 1.0f, 1.0f, 1.0f });
	SkillString->SetSize(30.0f);
	SkillString->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	SkillString->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	SkillString->SetString(L"½ºÅ³ À§Ä¡");
	ItemString = PlayerOrderObj->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	ItemString->SetColor(255, 255, 255, 255);
	ItemString->SetSubPivot({ WinSize.x * -0.075f, WinSize.y * -0.03f, 0.0f });
	ItemString->SetSubScale({ 1.0f, 1.0f, 1.0f });
	ItemString->SetSize(30.0f);
	ItemString->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	ItemString->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	ItemString->SetString(L"¾ÆÀÌÅÛ À§Ä¡");
	AttackString->HideFont();
	SkillString->HideFont();
	ItemString->HideFont();
	PlayerOrderWindow->HideWindow();

	PlayerSkillObj = GetScene()->CreateObject(L"PlayerSkillObject", UILayer);
	PlayerSkillWindow = PlayerSkillObj->AddComponent<NTPieceWindow>(11, 3, 0.5f);
	PlayerSkillObj->GetTransform()->SetLocalPosition({ WinSize.x * -0.125f, WinSize.y * -0.375f, 5.0f });
	PlayerSkillWindow->HideWindow();

	PlayerItemObj = GetScene()->CreateObject(L"PlayerItemObject", UILayer);
	PlayerItemWindow = PlayerItemObj->AddComponent<NTPieceWindow>(15, 3, 0.5f);
	PlayerItemObj->GetTransform()->SetLocalPosition({ WinSize.x * 0.0f, WinSize.y * -0.375f, 5.0f });
	PlayerItemWindow->HideWindow();
	
	Cursor = AddComponent<NTSpRenderer>(L"WindowUI.png", UILayer);
	Cursor->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Cursor->SetImageIndex(14);
	Cursor->SetSubScale({ 192.0f, 192.0f, 1.0f });
	Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.34f, 5.0f });
	Cursor->SetColor(0.0f);
	bCursor = false;

	return true;
}

void BattleSystem::PreUpdate()
{
	if (GameSystem::GetBattlePhase() == false)
	{
		return;
	}

	if (BattlePlayerVector.size() > 0)
	{
#pragma region StringSet
		size_t Size = BattlePlayerVector.size();
		if (Size == 1)
		{
			Player01Name->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player01HP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player01MP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player01TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player01Name->SetColor(255, 255, 255, 255);
			Player01HP->SetColor(255, 255, 255, 255);
			Player01MP->SetColor(255, 255, 255, 255);
			Player01TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[0]->GetComponent<NTBattle>()->GetCount());
		}
		else if (Size == 2)
		{
			Player01Name->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player01HP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player01MP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player01TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player01Name->SetColor(255, 255, 255, 255);
			Player01HP->SetColor(255, 255, 255, 255);
			Player01MP->SetColor(255, 255, 255, 255);
			Player02Name->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player02HP->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player02MP->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player02TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player02Name->SetColor(255, 255, 255, 255);
			Player02HP->SetColor(255, 255, 255, 255);
			Player02MP->SetColor(255, 255, 255, 255);
			Player01TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[0]->GetComponent<NTBattle>()->GetCount());
			Player02TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[1]->GetComponent<NTBattle>()->GetCount());
		}
		else if (Size == 3)
		{
			Player01Name->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player01HP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player01MP->SetString(BattlePlayerVector[0]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player01TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player01Name->SetColor(255, 255, 255, 255);
			Player01HP->SetColor(255, 255, 255, 255);
			Player01MP->SetColor(255, 255, 255, 255);
			Player02Name->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player02HP->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player02MP->SetString(BattlePlayerVector[1]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player02TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player02Name->SetColor(255, 255, 255, 255);
			Player02HP->SetColor(255, 255, 255, 255);
			Player02MP->SetColor(255, 255, 255, 255);
			Player03Name->SetString(BattlePlayerVector[2]->GetComponent<NTPlayer>()->GetStatus()->Name);
			Player03HP->SetString(BattlePlayerVector[2]->GetComponent<NTPlayer>()->GetStatus()->CurHP);
			Player03MP->SetString(BattlePlayerVector[2]->GetComponent<NTPlayer>()->GetStatus()->CurMP);
			Player03TurnBar->GetComponent<NTTurnBar>()->ShowBar();
			Player03Name->SetColor(255, 255, 255, 255);
			Player03HP->SetColor(255, 255, 255, 255);
			Player03MP->SetColor(255, 255, 255, 255);
			Player01TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[0]->GetComponent<NTBattle>()->GetCount());
			Player02TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[1]->GetComponent<NTBattle>()->GetCount());
			Player03TurnBar->GetComponent<NTTurnBar>()->SetPercentage(BattlePlayerVector[2]->GetComponent<NTBattle>()->GetCount());
		}
#pragma endregion
	}

	if (BattleEnemyList.size() > 0)
	{
		if (CurStatus == BWS_IDLE)
		{
			size_t Size = BattleEnemyList.size();

			std::list<Autoptr<NTObject>>::iterator StartIter = BattleEnemyList.begin();

			if (Size == 1)
			{
				EnemyList01->SetString(BattleEnemyList.front()->GetName());
				EnemyList01->SetColor(255, 255, 255, 255);
			}

			if (Size == 2)
			{

			}

			if (Size == 3)
			{

			}

			if (Size >= 4)
			{

			}
		}
		else 
		{
			size_t Size = BattleEnemyList.size();

			std::list<Autoptr<NTObject>>::iterator StartIter = BattleEnemyList.begin();

			if (Size == 1)
			{
				EnemyList01->HideFont();
			}

			if (Size == 2)
			{

			}

			if (Size == 3)
			{

			}

			if (Size >= 4)
			{

			}
		}
	}
	
}

void BattleSystem::MainUpdate()
{
	if (GameSystem::GetBattlePhase() == false)
	{
		return;
	}
	if (BattlePlayerVector[0]->GetComponent<NTBattle>()->IsTurn() == true)
	{
		if (bCursor == false)
		{
			Cursor->SetColor(1.0f);
			CurPlayerIndex = 0;
			bCursor = true;
		}
		TurnReady = true;
	}

	if (BattlePlayerVector[1]->GetComponent<NTBattle>()->IsTurn() == true)
	{
		if (bCursor == false)
		{
			Cursor->SetColor(1.0f);
			CurPlayerIndex = 1;
			bCursor = true;
		}
		TurnReady = true;
	}

	if (BattlePlayerVector[2]->GetComponent<NTBattle>()->IsTurn() == true)
	{
		if (bCursor == false)
		{
			Cursor->SetColor(1.0f);
			CurPlayerIndex = 2;
			bCursor = true;
		}
		TurnReady = true;
	}

	size_t All = 0;
	for (size_t i = 0; i < BattlePlayerVector.size(); i++)
	{
		if (BattlePlayerVector[i]->GetComponent<NTBattle>()->IsTurn() == false)
		{
			++All;
		}
	}

	if (All == BattlePlayerVector.size())
	{
		bCursor = false;
		Cursor->SetColor(0.0f);
	}

	ListIter = BattleEnemyList.begin();
	for (int i = 0; i < CurEnemyIndex; i++)
	{
		++ListIter;
	}

	switch (CurStatus)
	{
	case BattleSystem::BWS_IDLE:
		if (GameSystem::GetBattleReadyPhase() == true)
		{
			EnemyList01->SetColor(255, 255, 255, 255);
			EnemyList02->SetColor(255, 255, 255, 255);
			EnemyList03->SetColor(255, 255, 255, 255);
			EnemyList04->SetColor(255, 255, 255, 255);
		}
		switch (CurPlayerIndex)
		{
		case 0:
			Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.34f, 5.0f });
			break;
		case 1:
			Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.39f, 5.0f });
			break;
		case 2:
			Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.44f, 5.0f });
			break;
		default:
			break;
		}
		break;
	case BattleSystem::BWS_TURN:
		EnemyList01->HideFont();
		EnemyList02->HideFont();
		EnemyList03->HideFont();
		EnemyList04->HideFont();
		switch (CurOrderIndex)
		{
		case 0:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * -0.325f, 5.0f });
			break;
		case 1:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * -0.38f, 5.0f });
			break;
		case 2:
			Cursor->SetSubPivot({ WinSize.x * -0.45f, WinSize.y * -0.45f, 5.0f });
			break;
		default:
			break;
		}
		break;
	case BattleSystem::BWS_ATTACK:
		AttackString->SetColor(255, 255, 255, 255);
		SkillString->SetColor(255, 255, 255, 255);
		ItemString->SetColor(255, 255, 255, 255);
		Cursor->SetSubPivot((*ListIter)->GetTransform()->GetLocalPosition() + NTVEC{-50.0f, 0.0f, 101.0f});
		break;
	case BattleSystem::BWS_SKILL:
		break;
	case BattleSystem::BWS_ITEM:
		break;
	case BattleSystem::BWS_MAX:
	default:
		break;
	}
	

	if (TurnReady == true)
	{
		if (InputSystem::IsDown(L"ArrowUp") == true)
		{
			switch (CurStatus)
			{
			case BattleSystem::BWS_IDLE:
				switch (CurPlayerIndex)
				{
				case 0:
					break;
				case 1:
					if (BattlePlayerVector[0]->GetComponent<NTBattle>()->IsTurn() == true)
					{
						Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.34f, 5.0f });
						--CurPlayerIndex;
					}
					break;
				case 2:
					if (BattlePlayerVector[1]->GetComponent<NTBattle>()->IsTurn() == true)
					{
						Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.39f, 5.0f });
						--CurPlayerIndex;
					}
					break;
				default:
					break;
				}
				break;
			case BattleSystem::BWS_TURN:
				switch (CurOrderIndex)
				{
				case 0:
					break;
				case 1:
					--CurOrderIndex;
					break;
				case 2:
					--CurOrderIndex;
					break;
				default:
					break;
				}
				break;
			case BattleSystem::BWS_ATTACK:
				break;
			case BattleSystem::BWS_SKILL:
				break;
			case BattleSystem::BWS_ITEM:
				break;
			case BattleSystem::BWS_MAX:
			default:
				break;
			}
		}

		if (InputSystem::IsDown(L"ArrowDown") == true)
		{
			switch (CurStatus)
			{
			case BattleSystem::BWS_IDLE:
				switch (CurPlayerIndex)
				{
				case 0:
					if (BattlePlayerVector[1]->GetComponent<NTBattle>()->IsTurn() == true)
					{
						Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.39f, 5.0f });
						++CurPlayerIndex;
					}
					break;
				case 1:
					if (BattlePlayerVector[2]->GetComponent<NTBattle>()->IsTurn() == true)
					{
						Cursor->SetSubPivot({ WinSize.x * -0.11f, WinSize.y * -0.44f, 5.0f });
						++CurPlayerIndex;
					}
					break;
				case 2:
					break;
				default:
					break;
				}
				break;
			case BattleSystem::BWS_TURN:
				switch (CurOrderIndex)
				{
				case 0:
					++CurOrderIndex;
					break;
				case 1:
					++CurOrderIndex;
					break;
				case 2:
					break;
				default:
					break;
				}
				break;
				break;
			case BattleSystem::BWS_ATTACK:
				break;
			case BattleSystem::BWS_SKILL:
				break;
			case BattleSystem::BWS_ITEM:
				break;
			case BattleSystem::BWS_MAX:
			default:
				break;
			}
		
		}

		if (InputSystem::IsDown(L"Key1") == true)
		{
			if (CurStatus == BWS_IDLE)
			{
				CurStatus = BWS_TURN;
				CurOrderIndex = 0;
			}
			else if (CurStatus == BWS_TURN && CurOrderIndex == 0)
			{
				CurStatus = BWS_ATTACK;
			}
			else if (CurStatus == BWS_ATTACK)
			{
				BattlePlayerVector[CurPlayerIndex]->GetComponent<NTPlayer>()->SetAttack((*ListIter)->GetTransform()->GetLocalPosition(), 500.0f, L"HitUp");
				(*ListIter)->GetComponent<NTEnemy>()->Damage();
			}
		}

		if (InputSystem::IsDown(L"Key2") == true)
		{
			if (CurStatus == BWS_TURN)
			{
				CurStatus = BWS_IDLE;
			}
			else if (CurStatus == BWS_ATTACK)
			{
				CurStatus = BWS_TURN;
			}
		}
	}
	
}

void BattleSystem::AfterUpdate()
{
	if (GameSystem::GetBattlePhase() == false)
	{
		return;
	}

	if (GameSystem::GetBattleReadyPhase() == false)
	{
		int PCount = 0;
		for (size_t i = 0; i < BattlePlayerVector.size(); i++)
		{
			if (BattlePlayerVector[i]->GetComponent<NTBattle>()->IsReady() == true)
			{
				++PCount;
			}
		}

		std::list<Autoptr<NTObject>>::iterator ListStartIter = BattleEnemyList.begin();
		std::list<Autoptr<NTObject>>::iterator ListEndIter = BattleEnemyList.end();

		int ECount = 0;

		for (; ListStartIter != ListEndIter; ++ListStartIter)
		{
			if ((*ListStartIter)->GetComponent<NTBattle>()->IsReady() == true)
			{
				++ECount;
			}
		}

		if ((PCount == BattlePlayerVector.size()) && (ECount == BattleEnemyList.size()))
		{
			GameSystem::SetBattleReadyPhase(true);
			EnemyListWindow->ShowWindow();
			PlayerStatusWindow->ShowWindow();
			Autoptr<NTObject> Tmp = GetScene()->FindObject(L"UIObj", UILayer);
			Tmp->GetComponent<NTSoundPlayer>()->StopSound();
			Tmp->GetComponent<NTSoundPlayer>()->SoundPlay(L"BattleTheme.wav");
			for (size_t i = 0; i < BattlePlayerVector.size(); i++)
			{
				BattlePlayerVector[i]->GetComponent<NTPlayer>()->GetCurAnimator()->ChangeAnimation(L"WeaponIdleUp");
			}
			CurStatus = BWS_IDLE;
		}
		else
			GameSystem::SetBattleReadyPhase(false);
	}
	else
	{
	
	}
	
}

void BattleSystem::DbgRender()
{
}

void BattleSystem::CalDamage(Autoptr<NTObject> _Attacker, Autoptr<NTObject> _Target)
{
	_Attacker;
}

void BattleSystem::SetPlayerPosition()
{
	size_t PlayerCount = BattlePlayerVector.size();
	NTVEC WinSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	if (PlayerCount == 1)
	{
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetMove({ 0.0f, WinSize.y * -0.2f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ 0.0f, WinSize.y * -0.2f });
	}

	if (PlayerCount == 2)
	{
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetMove({ 0.0f, WinSize.y * -0.2f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ 0.0f, WinSize.y * -0.2f });
		BattlePlayerVector[1]->GetComponent<NTPlayer>()->SetMove({ WinSize.x * -0.2f, WinSize.y * -0.15f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ WinSize.x * -0.2f, WinSize.y * -0.15f });
	}

	if (PlayerCount == 3)
	{
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetMove({ 0.0f, WinSize.y * -0.2f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ 0.0f, WinSize.y * -0.2f });
		BattlePlayerVector[1]->GetComponent<NTPlayer>()->SetMove({ WinSize.x * -0.2f, WinSize.y * -0.15f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ WinSize.x * -0.2f, WinSize.y * -0.15f });
		BattlePlayerVector[2]->GetComponent<NTPlayer>()->SetMove({ WinSize.x * 0.2f, WinSize.y * -0.15f }, 500.0f, L"WeaponReadyUp");
		BattlePlayerVector[0]->GetComponent<NTPlayer>()->SetBattlePos({ WinSize.x * 0.2f, WinSize.y * -0.15f });
	}
}

void BattleSystem::EnterBattle(std::list<Autoptr<NTObject>>* _EnemyList)
{
	SceneCamera->GetComponent<FieldCamera>()->SetUpdate(false);
	GameSystem::SetBattlePhase(true);

	BattleEnemyList = *_EnemyList;

	std::list<Autoptr<NTObject>>::iterator ListStartIter = BattleEnemyList.begin();
	std::list<Autoptr<NTObject>>::iterator ListEndIter = BattleEnemyList.end();

	for (; ListStartIter != ListEndIter; ++ListStartIter)
	{
		if ((*ListStartIter)->GetComponent<NT2DCollision>() != nullptr)
		{
			(*ListStartIter)->GetComponent<NT2DCollision>()->SetUpdate(false);
		}
	}

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
	// ±×³É ÇÈ¼¿Ã¼Ä¿ ¾÷µ¥ÀÌÆ®¿¡¼­ ¹èÆ²ÁßÀÌ¸é ¾ÈÇÏ°Ô ÇØÁÖÀÚ. ¿¡ÈÞ..

	for (size_t i = 0; i < BattlePlayerVector.size(); i++)
	{
		if (BattlePlayerVector[i]->GetComponent<NTPixelChecker>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NTPixelChecker>()->SetUpdate(false);
		}

		if (BattlePlayerVector[i]->GetComponent<NT2DCollision>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NT2DCollision>()->SetUpdate(false);
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
	std::list<Autoptr<NTObject>>::iterator ListStartIter = BattleEnemyList.begin();
	std::list<Autoptr<NTObject>>::iterator ListEndIter = BattleEnemyList.end();

	for (; ListStartIter != ListEndIter; ++ListStartIter)
	{
		if ((*ListStartIter)->GetComponent<NT2DCollision>() != nullptr)
		{
			(*ListStartIter)->GetComponent<NT2DCollision>()->SetUpdate(true);
		}
	}

	for (size_t i = 0; i < BattlePlayerVector.size(); i++)
	{
		if (BattlePlayerVector[i]->GetComponent<NTPixelChecker>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NTPixelChecker>()->SetUpdate(true);
		}

		if (BattlePlayerVector[i]->GetComponent<NT2DCollision>() != nullptr)
		{
			BattlePlayerVector[i]->GetComponent<NT2DCollision>()->SetUpdate(true);
		}
	}

	BattlePlayerVector.clear();
	BattleEnemyList.clear();
}