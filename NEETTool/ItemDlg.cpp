// ItemDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemDlg.h"
#include "afxdialogex.h"

#include <NTWinShortCut.h>
#include <NTScene.h>
#include <NTWeapon.h>
#include <NTArmor.h>
#include <NTHelmet.h>
#include <NTAcc.h>
#include <NTConsume.h>
#include <NTKeyItem.h>
#include <ResourceSystem.h>
#include <NTWriteStream.h>
#include <NTReadStream.h>
#include <NTItemData.h>

#include "ItemView.h"
#include "NTDlgShortCut.h"


// ItemDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ItemDlg, TabDlg)

ItemDlg::ItemDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_ItemDlg, pParent), CurItem(nullptr)
{

}

ItemDlg::~ItemDlg()
{
	Release();
}

void ItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEMTREE, ItemTree);
}


BEGIN_MESSAGE_MAP(ItemDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemDlg::OnBnClickedCancel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ITEMTREE, &ItemDlg::OnTvnSelchangedItemtree)
	ON_BN_CLICKED(IDC_CREATEITEM, &ItemDlg::OnBnClickedCreateitem)
	ON_BN_CLICKED(IDC_ITEMSAVE, &ItemDlg::OnBnClickedItemsave)
	ON_BN_CLICKED(IDC_ITEMLOAD, &ItemDlg::OnBnClickedItemload)
END_MESSAGE_MAP()


// ItemDlg �޽��� ó�����Դϴ�.


void ItemDlg::OnBnClickedOk()
{

}


void ItemDlg::OnBnClickedCancel()
{

}


void ItemDlg::OnTvnSelchangedItemtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	CurItem = pNMTreeView->itemNew.hItem;

	NTItem* Item = (NTItem*)ItemTree.GetItemData(CurItem);

	if (nullptr != Item)
	{
		NTDlgShortCut::pItemView->ClearDlg();
		NTDlgShortCut::pItemView->SetItem(Item);
	}


}

void ItemDlg::InitDlg()
{
	Autoptr<NTScene> Scene = NTWinShortCut::GetMainSceneSystem().FindScene(L"ItemDlg");
}


BOOL ItemDlg::OnInitDialog()
{
	TabDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CCreateContext Context;

	Context.m_pNewViewClass = RUNTIME_CLASS(ItemView);

	ItemView* View = (ItemView*)((CFrameWnd*)this)->CreateView(&Context);

	RECT ViewSize = { 300, 18, 950, 750 };
	View->ShowWindow(SW_SHOW);
	View->MoveWindow(&ViewSize);

	SetBaseTree();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void ItemDlg::OnBnClickedCreateitem()
{
	if (CurItem != nullptr)
	{
		if (ItemTree.GetItemData(CurItem) == (DWORD_PTR)nullptr)
		{
			std::wstring Temp = ItemTree.GetItemText(CurItem);
			if (lstrcmpW(Temp.c_str(), L"Weapon") == 0)
			{
				CreateItem<NTWeapon>();
			}

			if (lstrcmpW(Temp.c_str(), L"Helmet") == 0)
			{
				CreateItem<NTHelmet>();
			}

			if (lstrcmpW(Temp.c_str(), L"Armor") == 0)
			{
				CreateItem<NTArmor>();
			}

			if (lstrcmpW(Temp.c_str(), L"Accessory") == 0)
			{
				CreateItem<NTAcc>();
			}

			if (lstrcmpW(Temp.c_str(), L"Consumable") == 0)
			{
				CreateItem<NTConsume>();
			}

			if (lstrcmpW(Temp.c_str(), L"KeyItem") == 0)
			{
				CreateItem<NTKeyItem>();
			}
		}
	}
}

void ItemDlg::OnBnClickedItemsave()
{
	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"ItemData.neet";

	CString BackupData = PathSystem::FindPath(L"ItemBackups");

	wchar_t Time[256] = {};

	_itow_s((int)time(nullptr), Time, 36);

	BackupData += L"Backup_";
	BackupData += Time;
	BackupData += L".bak";

	NTWriteStream SaveStream = NTWriteStream(SaveData);
	NTWriteStream BackupStream = NTWriteStream(BackupData);

	int size = (int)ItemMap.size();
	SaveStream.Write(&size, sizeof(int));
	BackupStream.Write(&size, sizeof(int));

	std::unordered_map<std::wstring, NTItem*>::iterator StartIter = ItemMap.begin();
	std::unordered_map<std::wstring, NTItem*>::iterator EndIter = ItemMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		const type_info* Type = StartIter->second->GetType();

		const char* TypeName = Type->name();
		char TypeNameBuf[20];
		strcpy_s(TypeNameBuf, TypeName);
		SaveStream.Write(TypeNameBuf, sizeof(TypeNameBuf));
		BackupStream.Write(TypeNameBuf, sizeof(TypeNameBuf));

		NTItemData NewData = {};

		if (strcmp(TypeName, "class NTWeapon") == 0)
		{
			NTWeapon Weapon = *(NTWeapon*)(StartIter->second);
			NewData.bSpecial = Weapon.bSpecial;
			NewData.Crit = Weapon.Crit;
			lstrcpyW(NewData.Info, Weapon.Info.c_str());
			lstrcpyW(NewData.Name, Weapon.GetName());
			lstrcpyW(NewData.Output, Weapon.Output.c_str());
			NewData.Price = Weapon.Price;
			NewData.Sellable = Weapon.Sellable;
			NewData.Stat = Weapon.Atk;
			NewData.Type = (int)Weapon.Type;
			NewData.UseCharacter = Weapon.Only;
		}

		if (strcmp(TypeName, "class NTArmor") == 0)
		{
			NTArmor Armor = *(NTArmor*)(StartIter->second);
			NewData.bSpecial = Armor.bSpecial;
			NewData.Crit = -1;
			lstrcpyW(NewData.Info, Armor.Info.c_str());
			lstrcpyW(NewData.Name, Armor.GetName());
			lstrcpyW(NewData.Output, Armor.Output.c_str());
			NewData.Price = Armor.Price;
			NewData.Sellable = Armor.Sellable;
			NewData.Stat = Armor.Def;
			NewData.Type = (int)Armor.Type;
			NewData.UseCharacter = Armor.Only;
		}

		if (strcmp(TypeName, "class NTHelmet") == 0)
		{
			NTHelmet Helmet = *(NTHelmet*)(StartIter->second);
			NewData.bSpecial = Helmet.bSpecial;
			NewData.Crit = -1;
			lstrcpyW(NewData.Info, Helmet.Info.c_str());
			lstrcpyW(NewData.Name, Helmet.GetName());
			lstrcpyW(NewData.Output, Helmet.Output.c_str());
			NewData.Price = Helmet.Price;
			NewData.Sellable = Helmet.Sellable;
			NewData.Stat = Helmet.Def;
			NewData.Type = -1;
			NewData.UseCharacter = Helmet.Only;
		}

		if (strcmp(TypeName, "class NTAcc") == 0)
		{
			NTAcc Acc = *(NTAcc*)(StartIter->second);
			NewData.bSpecial = Acc.bSpecial;
			NewData.Crit = -1;
			lstrcpyW(NewData.Info, Acc.Info.c_str());
			lstrcpyW(NewData.Name, Acc.GetName());
			lstrcpyW(NewData.Output, Acc.Output.c_str());
			NewData.Price = Acc.Price;
			NewData.Sellable = Acc.Sellable;
			NewData.Stat = -1;
			NewData.Type = -1;
			NewData.UseCharacter = Acc.Only;
		}

		if (strcmp(TypeName, "class NTConsume") == 0)
		{
			NTConsume Consume = *(NTConsume*)(StartIter->second);
			NewData.bSpecial = false;
			NewData.Crit = -1;
			lstrcpyW(NewData.Info, Consume.Info.c_str());
			lstrcpyW(NewData.Name, Consume.GetName());
			lstrcpyW(NewData.Output, Consume.Output.c_str());
			NewData.Price = Consume.Price;
			NewData.Sellable = Consume.Sellable;
			NewData.Stat = -1;
			NewData.Type = -1;
			NewData.UseCharacter = -1;
		}

		if (strcmp(TypeName, "class NTKeyItem") == 0)
		{
			NTKeyItem KeyItem = *(NTKeyItem*)(StartIter->second);
			NewData.bSpecial = false;
			NewData.Crit = -1;
			lstrcpyW(NewData.Info, KeyItem.Info.c_str()); 
			lstrcpyW(NewData.Name, KeyItem.GetName());
			lstrcpyW(NewData.Output, KeyItem.Output.c_str());
			NewData.Price = KeyItem.Price;
			NewData.Sellable = KeyItem.Sellable;
			NewData.Stat = -1;
			NewData.Type = -1;
			NewData.UseCharacter = -1;
		}

		SaveStream.Write(&NewData, sizeof(NTItemData));
		BackupStream.Write(&NewData, sizeof(NTItemData));
	}
}


void ItemDlg::OnBnClickedItemload()
{
	Release();
	ItemTree.DeleteAllItems();
	CurItem = nullptr;
	SetBaseTree();

	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"ItemData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData);

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		char TypeNameBuf[20];
		ReadStream.Read(TypeNameBuf, sizeof(TypeNameBuf), sizeof(TypeNameBuf));
		NTItemData* NewItem = new NTItemData();
		ReadStream.Read(NewItem, sizeof(NTItemData), sizeof(NTItemData));

		if (strcmp(TypeNameBuf, "class NTWeapon") == 0)
		{
			NTWeapon* NewWeapon = new NTWeapon();
			NewWeapon->Atk = NewItem->Stat;
			NewWeapon->bSpecial = NewItem->bSpecial;
			NewWeapon->Crit = NewItem->Crit;
			NewWeapon->SetName(NewItem->Name);
			NewWeapon->Info = NewItem->Info;
			NewWeapon->Only = (CHARACTER)NewItem->UseCharacter;
			NewWeapon->Output = NewItem->Output;
			NewWeapon->Price = NewItem->Price;
			NewWeapon->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NewWeapon->Type = (NTWeapon::WEAPONTYPE)NewItem->Type;
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewWeapon->GetName(), NewWeapon));

			HTREEITEM NewItem = ItemTree.InsertItem(NewWeapon->GetName(), TreeWeapon);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewWeapon));
			ItemTree.Expand(TreeWeapon, TVE_EXPAND);
		}

		if (strcmp(TypeNameBuf, "class NTArmor") == 0)
		{
			NTArmor* NewArmor = new NTArmor();
			NewArmor->Def = NewItem->Stat;
			NewArmor->bSpecial = NewItem->bSpecial;
			NewArmor->SetName(NewItem->Name);
			NewArmor->Info = NewItem->Info;
			NewArmor->Only = (CHARACTER)NewItem->UseCharacter;
			NewArmor->Output = NewItem->Output;
			NewArmor->Price = NewItem->Price;
			NewArmor->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NewArmor->Type = (NTArmor::ARMORTYPE)NewItem->Type;
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewArmor->GetName(), NewArmor));

			HTREEITEM NewItem = ItemTree.InsertItem(NewArmor->GetName(), TreeArmor);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewArmor));
			ItemTree.Expand(TreeArmor, TVE_EXPAND);
		}

		if (strcmp(TypeNameBuf, "class NTHelmet") == 0)
		{
			NTHelmet* NewHelmet = new NTHelmet();
			NewHelmet->Def = NewItem->Stat;
			NewHelmet->bSpecial = NewItem->bSpecial;
			NewHelmet->SetName(NewItem->Name);
			NewHelmet->Info = NewItem->Info;
			NewHelmet->Only = (CHARACTER)NewItem->UseCharacter;
			NewHelmet->Output = NewItem->Output;
			NewHelmet->Price = NewItem->Price;
			NewHelmet->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewHelmet->GetName(), NewHelmet));

			HTREEITEM NewItem = ItemTree.InsertItem(NewHelmet->GetName(), TreeHelmet);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewHelmet));
			ItemTree.Expand(TreeHelmet, TVE_EXPAND);
		}

		if (strcmp(TypeNameBuf, "class NTAcc") == 0)
		{
			NTAcc* NewAcc = new NTAcc();
			NewAcc->bSpecial = NewItem->bSpecial;
			NewAcc->SetName(NewItem->Name);
			NewAcc->Info = NewItem->Info;
			NewAcc->Only = (CHARACTER)NewItem->UseCharacter;
			NewAcc->Output = NewItem->Output;
			NewAcc->Price = NewItem->Price;
			NewAcc->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewAcc->GetName(), NewAcc));

			HTREEITEM NewItem = ItemTree.InsertItem(NewAcc->GetName(), TreeAcc);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewAcc));
			ItemTree.Expand(TreeAcc, TVE_EXPAND);
		}

		if (strcmp(TypeNameBuf, "class NTConsume") == 0)
		{
			NTConsume* NewConsume = new NTConsume();
			NewConsume->SetName(NewItem->Name);
			NewConsume->Info = NewItem->Info;
			NewConsume->Output = NewItem->Output;
			NewConsume->Price = NewItem->Price;
			NewConsume->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewConsume->GetName(), NewConsume));

			HTREEITEM NewItem = ItemTree.InsertItem(NewConsume->GetName(), TreeConsume);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewConsume));
			ItemTree.Expand(TreeConsume, TVE_EXPAND);
		}

		if (strcmp(TypeNameBuf, "class NTKeyItem") == 0)
		{
			NTKeyItem* NewKeyItem = new NTKeyItem();
			NewKeyItem->SetName(NewItem->Name);
			NewKeyItem->Info = NewItem->Info;
			NewKeyItem->Output = NewItem->Output;
			NewKeyItem->Price = NewItem->Price;
			NewKeyItem->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(NewKeyItem->GetName(), NewKeyItem));

			HTREEITEM NewItem = ItemTree.InsertItem(NewKeyItem->GetName(), TreeKeyItem);
			ItemTree.SetItemData(NewItem, (DWORD_PTR)&(*NewKeyItem));
			ItemTree.Expand(TreeKeyItem, TVE_EXPAND);
		}

		delete NewItem;
	}
}

void ItemDlg::SetBaseTree()
{
	HTREEITEM Equip = ItemTree.InsertItem(L"Equip");
	ItemTree.SetItemData(Equip, (DWORD_PTR)nullptr);

	TreeWeapon = ItemTree.InsertItem(L"Weapon", Equip);
	ItemTree.SetItemData(TreeWeapon, (DWORD_PTR)nullptr);
	TreeHelmet = ItemTree.InsertItem(L"Helmet", Equip);
	ItemTree.SetItemData(TreeHelmet, (DWORD_PTR)nullptr);
	TreeArmor = ItemTree.InsertItem(L"Armor", Equip);
	ItemTree.SetItemData(TreeArmor, (DWORD_PTR)nullptr);
	TreeAcc = ItemTree.InsertItem(L"Accessory", Equip);
	ItemTree.SetItemData(TreeAcc, (DWORD_PTR)nullptr);
	ItemTree.Expand(Equip, TVE_EXPAND);

	TreeConsume = ItemTree.InsertItem(L"Consumable");
	ItemTree.SetItemData(TreeConsume, (DWORD_PTR)nullptr);
	TreeKeyItem = ItemTree.InsertItem(L"KeyItem");
	ItemTree.SetItemData(TreeKeyItem, (DWORD_PTR)nullptr);
}

void ItemDlg::Release()
{
	std::unordered_map<std::wstring, NTItem*>::iterator StartIter = ItemMap.begin();
	std::unordered_map<std::wstring, NTItem*>::iterator EndIter = ItemMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		delete StartIter->second;
	}

	ItemMap.clear();
}
