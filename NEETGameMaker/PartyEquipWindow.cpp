#include "PartyEquipWindow.h"

#include "NTPieceWindow.h"
#include "GameValue.h"
#include "PartyWindow.h"
#include "NTWeapon.h"

#include <NTWinShortCut.h>
#include <NTScene.h>
#include <NTFontRenderer.h>
#include <InputSystem.h>

PartyEquipWindow::PartyEquipWindow() : InventoryWindow(nullptr), EquipWindow(nullptr), bUp(false), CurIndex(-1), CurPlayer(nullptr), bShow(false), InventoryIndex(nullptr)
, InventoryScroll(0)
{
	Inventory.reserve(10);
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
	EquipType->SetSubPivot({ WinSize.x * 0.18f, WinSize.y * 0.335f });
	EquipType->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipType->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EquipType->SetString(L"");

	for (size_t i = 0; i < 9; i++)
	{
		Autoptr<NTFontRenderer> Tmp = GetNTObject()->AddComponent<NTFontRenderer>(L"궁서", UILayer);
		Inventory.push_back(Tmp);
		Tmp->SetColor(255, 255, 255, 255);
		Tmp->SetSubScale({ 1.0f, 1.0f, 1.0f });
		Tmp->SetSize(25.0f);
		Tmp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
		Tmp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
		Tmp->SetString(L"");
		Inventory[i]->SetSubPivot({ WinSize.x * 0.0f + WinSize.x * 0.12f, WinSize.y * (0.055f * (i + 1)) + WinSize.y * 0.41f });
	}

	PauseRender();

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
				TypeInventory = GameSystem::GetInventory().GetTypeList("class NTWeapon");
				std::list<Autoptr<InventoryData>>::iterator StartIter = TypeInventory.begin();
				std::list<Autoptr<InventoryData>>::iterator EndIter = TypeInventory.end();
				for (; StartIter != EndIter;)
				{
					void* Tmp = (*StartIter)->Item;
					NTWeapon* Check = (NTWeapon*)Tmp;
					if (Check->WeaponType != CurPlayer->Weapon.WeaponType)
					{
						StartIter = TypeInventory.erase(StartIter);
					}
					else
						++StartIter;
				}
				StartIter = TypeInventory.begin();
				EndIter = TypeInventory.end();

				if (InventoryIndex != nullptr)
				{
					if ((*InventoryIndex) == 9)
					{
						++InventoryScroll;
						--(*InventoryIndex);
					}

					if ((*InventoryIndex) == -1)
					{
						--InventoryScroll;
						++(*InventoryIndex);
					}
				}

				if (InventoryScroll >= (int)TypeInventory.size() - 9)
				{
					InventoryScroll = (int)TypeInventory.size() - 9;
				}

				if (InventoryScroll < 0)
				{
					InventoryScroll = 0;
				}

				for (int i = 0; i < InventoryScroll; i++)
				{
					++StartIter;
				}

				for (size_t i = 0; i < 9; ++i, ++StartIter)
				{
					Inventory[i]->SetString((*StartIter)->Item->Output.c_str());
				}
			}
			else if (CurDetailIndex == 1)
			{
				EquipType->SetString(L"머       리");
				TypeInventory = GameSystem::GetInventory().GetTypeList("class NTHelmet");
				std::list<Autoptr<InventoryData>>::iterator StartIter = TypeInventory.begin();
				std::list<Autoptr<InventoryData>>::iterator EndIter = TypeInventory.end();
				for (; StartIter != EndIter;)
				{
					NTEquip* Check = (NTEquip*)(*StartIter)->Item;
					if (Check->Only[CurChara] == false)
					{
						StartIter = TypeInventory.erase(StartIter);
					}
					else
						++StartIter;
				}
				StartIter = TypeInventory.begin();
				EndIter = TypeInventory.end();

				if (InventoryIndex != nullptr)
				{
					if ((*InventoryIndex) == 9)
					{
						++InventoryScroll;
						--(*InventoryIndex);
					}

					if ((*InventoryIndex) == -1)
					{
						--InventoryScroll;
						++(*InventoryIndex);
					}
				}

				if (InventoryScroll >= (int)TypeInventory.size() - 9)
				{
					InventoryScroll = (int)TypeInventory.size() - 9;
				}

				if (InventoryScroll < 0)
				{
					InventoryScroll = 0;
				}

				for (int i = 0; i < InventoryScroll; i++)
				{
					++StartIter;
				}

				for (size_t i = 0; i < 9; ++i, ++StartIter)
				{
					Inventory[i]->SetString((*StartIter)->Item->Output.c_str());
				}
			}
			else if (CurDetailIndex == 2)
			{
				EquipType->SetString(L"방  어  구");
				TypeInventory = GameSystem::GetInventory().GetTypeList("class NTArmor");
				std::list<Autoptr<InventoryData>>::iterator StartIter = TypeInventory.begin();
				std::list<Autoptr<InventoryData>>::iterator EndIter = TypeInventory.end();
				for (; StartIter != EndIter;)
				{
					NTEquip* Check = (NTEquip*)(*StartIter)->Item;
					if (Check->Only[CurChara] == false)
					{
						StartIter = TypeInventory.erase(StartIter);
					}
					else
						++StartIter;
				}
				StartIter = TypeInventory.begin();
				EndIter = TypeInventory.end();

				if (InventoryIndex != nullptr)
				{
					if ((*InventoryIndex) == 9)
					{
						++InventoryScroll;
						--(*InventoryIndex);
					}

					if ((*InventoryIndex) == -1)
					{
						--InventoryScroll;
						++(*InventoryIndex);
					}
				}

				if (InventoryScroll >= (int)TypeInventory.size() - 9)
				{
					InventoryScroll = (int)TypeInventory.size() - 9;
				}

				if (InventoryScroll < 0)
				{
					InventoryScroll = 0;
				}

				for (int i = 0; i < InventoryScroll; i++)
				{
					++StartIter;
				}

				for (size_t i = 0; i < 9; ++i, ++StartIter)
				{
					Inventory[i]->SetString((*StartIter)->Item->Output.c_str());
				}
			}
			else if (CurDetailIndex == 3)
			{
				EquipType->SetString(L"장  신  구");
				TypeInventory = GameSystem::GetInventory().GetTypeList("class NTAcc");
				std::list<Autoptr<InventoryData>>::iterator StartIter = TypeInventory.begin();
				std::list<Autoptr<InventoryData>>::iterator EndIter = TypeInventory.end();
				for (; StartIter != EndIter;)
				{
					NTEquip* Check = (NTEquip*)(*StartIter)->Item;
					if (Check->Only[CurChara] == false)
					{
						StartIter = TypeInventory.erase(StartIter);
					}
					else
						++StartIter;
				}
				StartIter = TypeInventory.begin();
				EndIter = TypeInventory.end();

				if (InventoryIndex != nullptr)
				{
					if ((*InventoryIndex) == 9)
					{
						++InventoryScroll;
						--(*InventoryIndex);
					}

					if ((*InventoryIndex) == -1)
					{
						--InventoryScroll;
						++(*InventoryIndex);
					}
				}

				if (InventoryScroll >= (int)TypeInventory.size() - 9)
				{
					InventoryScroll = (int)TypeInventory.size() - 9;
				}

				if (InventoryScroll < 0)
				{
					InventoryScroll = 0;
				}

				for (int i = 0; i < InventoryScroll; i++)
				{
					++StartIter;
				}

				for (size_t i = 0; i < 9; ++i, ++StartIter)
				{
					Inventory[i]->SetString((*StartIter)->Item->Output.c_str());
				}
			}
		}
	}
}

void PartyEquipWindow::DbgRender()
{
}


void PartyEquipWindow::ChangeEquip()
{
	NTInventory& Tmp = GameSystem::GetInventory();
	std::list<Autoptr<InventoryData>>::iterator StartIter = TypeInventory.begin();
	if (CurDetailIndex == 0)
	{
		for (int i = 0; i < InventoryScroll + (*InventoryIndex); i++)
		{
			++StartIter;
		}
		NTItem* Item = NTItem::FindItem((*StartIter)->Item->GetName());
		Tmp.InsertItem(NTItem::FindItem(CurPlayer->Weapon.GetName()));
		Tmp.TakeoutItem(NTItem::FindItem((*StartIter)->Item->GetName()));
		CurPlayer->Weapon = *(NTWeapon*)Item;

		InventoryScroll = 0;
		(*InventoryIndex) = 0;
	}
	else if (CurDetailIndex == 1)
	{
		for (int i = 0; i < InventoryScroll + (*InventoryIndex); i++)
		{
			++StartIter;
		}
		NTItem* Item = NTItem::FindItem((*StartIter)->Item->GetName());
		Tmp.InsertItem(NTItem::FindItem(CurPlayer->Helmet.GetName()));
		Tmp.TakeoutItem(NTItem::FindItem((*StartIter)->Item->GetName()));
		CurPlayer->Helmet = *(NTHelmet*)Item;

		InventoryScroll = 0;
		(*InventoryIndex) = 0;
	}
	else if (CurDetailIndex == 2)
	{
		for (int i = 0; i < InventoryScroll + (*InventoryIndex); i++)
		{
			++StartIter;
		}
		NTItem* Item = NTItem::FindItem((*StartIter)->Item->GetName());
		Tmp.InsertItem(NTItem::FindItem(CurPlayer->Armor.GetName()));
		Tmp.TakeoutItem(NTItem::FindItem((*StartIter)->Item->GetName()));
		CurPlayer->Armor = *(NTArmor*)Item;

		InventoryScroll = 0;
		(*InventoryIndex) = 0;
	}
	else if (CurDetailIndex == 3)
	{
		for (int i = 0; i < InventoryScroll + (*InventoryIndex); i++)
		{
			++StartIter;
		}
		NTItem* Item = NTItem::FindItem((*StartIter)->Item->GetName());
		Tmp.InsertItem(NTItem::FindItem(CurPlayer->Acc.GetName()));
		Tmp.TakeoutItem(NTItem::FindItem((*StartIter)->Item->GetName()));
		CurPlayer->Acc = *(NTAcc*)Item;

		InventoryScroll = 0;
		(*InventoryIndex) = 0;
	}
}

void PartyEquipWindow::PauseRender()
{
	EquipType->SetColor(0);
	for (size_t i = 0; i < Inventory.size(); i++)
	{
		Inventory[i]->SetColor(0);
	}
	
}

void PartyEquipWindow::ResumeRender()
{
	EquipType->SetColor(255, 255, 255, 255);
	for (size_t i = 0; i < Inventory.size(); i++)
	{
		Inventory[i]->SetColor(255, 255, 255, 255);
	}
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
			ResumeRender();
		}
		else
		{
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, 750.0f * TimeSystem::DeltaTime() });
		}
	}

	if (CurIndex == 1)
	{
		Autoptr<NTObject> FindObj = GetNTObject()->GetParent()->FindChild(L"PartyLeftWindow02");

		if (GetNTObject()->GetTransform()->GetLocalPosition().y >= WinSize.y * -0.21f)
		{
			GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.205f });
			FindObj->GetTransform()->SetLocalPosition(PartyWindowFirstPos);
			bUp = false;
			Autoptr<PartyWindow> tmp = GetNTObject()->GetParent()->GetComponent<PartyWindow>();
			tmp->EnterDetail();
			bShow = true;
			ResumeRender();
		}
		else
		{
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, 750.0f * TimeSystem::DeltaTime() });
			if (GetNTObject()->GetTransform()->GetLocalPosition().y >= WinSize.y * -0.43f)
			{
				FindObj->GetTransform()->SetLocalMove({ 0.0f, 750.0f * TimeSystem::DeltaTime() });
			}
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
			PauseRender();
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, -750.0f * TimeSystem::DeltaTime() });
		}

	}

	if (CurIndex == 1)
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
			PauseRender();
			GetNTObject()->GetTransform()->SetLocalMove({ 0.0f, -750.0f * TimeSystem::DeltaTime() });
		}

	}
}