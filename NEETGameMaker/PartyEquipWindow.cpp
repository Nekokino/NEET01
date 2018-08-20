#include "PartyEquipWindow.h"

#include "NTPieceWindow.h"
#include "GameValue.h"
#include "PartyWindow.h"

#include <NTWinShortCut.h>
#include <NTScene.h>
#include <NTFontRenderer.h>

PartyEquipWindow::PartyEquipWindow() : InventoryWindow(nullptr), EquipWindow(nullptr), bUp(false), CurIndex(-1), CurPlayer(nullptr), bShow(false)
{
}


PartyEquipWindow::~PartyEquipWindow()
{
}

bool PartyEquipWindow::Init()
{
	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.88f, 0.0f });

	InventoryWindow = GetScene()->CreateObject(L"InventoryWindow", UILayer);
	GetNTObject()->AddChild(InventoryWindow);
	InventoryWindow->GetTransform()->SetLocalPosition(0.0f);
	

	EquipWindow = GetScene()->CreateObject(L"EquipWindow", UILayer);
	GetNTObject()->AddChild(EquipWindow);
	EquipWindow->GetTransform()->SetLocalPosition(0.0f);

	InventoryWindowRenderer = InventoryWindow->AddComponent<NTPieceWindow>(5, 8, 0.45f);
	TextWindowRenderer = EquipWindow->AddComponent<NTPieceWindow>(5, 2, 0.45f);
	
	EquipWindow->GetTransform()->SetLocalPosition({ 0.0f, WinSize.y * 0.35f});

	EquipType = GetNTObject()->AddComponent<NTFontRenderer>(L"궁서", UILayer);
	EquipType->SetColor(255, 255, 255, 255);
	EquipType->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipType->SetSize(25.0f);
	EquipType->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipType->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EquipType->SetString(L"ERROR");

	return true;
}

void PartyEquipWindow::MainUpdate()
{
	if (bUp == true)
	{
		MoveUp();
	}

	if (bDown == true)
	{
		MoveDown();
	}

	if (bShow == true)
	{
		if (CurPlayer != nullptr)
		{
			if (CurDetailIndex == 0)
			{
				EquipType->SetString(L"무       기");
				switch (CurPlayer->Weapon.WeaponType)
				{
				case NTWeapon::WEAPONTYPE::WT_ARM:
					break;
				case NTWeapon::WEAPONTYPE::WT_BOW:
					break;
				case NTWeapon::WEAPONTYPE::WT_BROADSWORD:
					break;
				case NTWeapon::WEAPONTYPE::WT_FIST:
					break;
				case NTWeapon::WEAPONTYPE::WT_GUN:
					break;
				case NTWeapon::WEAPONTYPE::WT_SCYTHE:
					break;
				case NTWeapon::WEAPONTYPE::WT_SWORD:
					break;
				default:
					break;
				}
			}
			else if (CurDetailIndex == 1)
			{
				EquipType->SetString(L"모       자");
			}
			else if (CurDetailIndex == 2)
			{
				EquipType->SetString(L"방  어  구");
			}
			else if (CurDetailIndex == 3)
			{
				EquipType->SetString(L"장  신  구");
			}
		}
	}
}

void PartyEquipWindow::DbgRender()
{
}


void PartyEquipWindow::MoveUp()
{
	if (CurIndex >= 3 || CurIndex <= -1)
	{
		return;
	}


	if (CurIndex == 0)
	{
		if (GetNTObject()->GetTransform()->GetLocalPosition().y >= WinSize.y * -0.21f)
		{
			GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.205f });
			bUp = false;
			Autoptr<PartyWindow> tmp = GetNTObject()->GetParent()->GetComponent<PartyWindow>();
			tmp->EnterDetail();
			bShow = true;
		}
		else
		{
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, 750.0f * TimeSystem::DeltaTime() });
		}
		
	}
	
}

void PartyEquipWindow::MoveDown()
{
	if (CurIndex >= 3 || CurIndex <= -1)
	{
		return;
	}

	if (CurIndex == 0)
	{
		if (GetNTObject()->GetTransform()->GetLocalPosition().y <= WinSize.y * -0.88f)
		{
			GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.88f });
			bDown = false;
			Autoptr<PartyWindow> tmp = GetNTObject()->GetParent()->GetComponent<PartyWindow>();
			tmp->ResumeRenderer();
			tmp->GetOutDetail();
		}
		else
		{
			bShow = false;
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, -750.0f * TimeSystem::DeltaTime() });
		}

	}
}