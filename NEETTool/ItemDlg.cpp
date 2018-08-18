// ItemDlg.cpp : 구현 파일입니다.
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


// ItemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ItemDlg, TabDlg)

ItemDlg::ItemDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_ItemDlg, pParent), CurItem(nullptr)
{
	NTDlgShortCut::pItemDlg = this;
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
	ON_NOTIFY(TVN_KEYDOWN, IDC_ITEMTREE, &ItemDlg::OnTvnKeydownItemtree)
END_MESSAGE_MAP()


// ItemDlg 메시지 처리기입니다.


void ItemDlg::OnBnClickedOk()
{

}


void ItemDlg::OnBnClickedCancel()
{

}


void ItemDlg::OnTvnSelchangedItemtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	CurItem = pNMTreeView->itemNew.hItem;

	NTItem* Item = nullptr;
	if (CurItem != nullptr)
	{
		Item = (NTItem*)ItemTree.GetItemData(CurItem);
	}
	
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CCreateContext Context;

	Context.m_pNewViewClass = RUNTIME_CLASS(ItemView);

	ItemView* View = (ItemView*)((CFrameWnd*)this)->CreateView(&Context);

	RECT ViewSize = { 300, 18, 950, 800 };
	View->ShowWindow(SW_SHOW);
	View->MoveWindow(&ViewSize);

	SetBaseTree();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
			NewData.Type = (int)Weapon.WeaponType;
			memcpy_s(NewData.Only, sizeof(NewData.Only), Weapon.Only, sizeof(NewData.Only));
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
			memcpy_s(NewData.Only, sizeof(NewData.Only), Armor.Only, sizeof(NewData.Only));
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
			memcpy_s(NewData.Only, sizeof(NewData.Only), Helmet.Only, sizeof(NewData.Only));
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
			memcpy_s(NewData.Only, sizeof(NewData.Only), Acc.Only, sizeof(NewData.Only));
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
			memset(NewData.Only, false, sizeof(NewData.Only));
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
			memset(NewData.Only, false, sizeof(NewData.Only));
		}

		SaveStream.Write(&NewData, sizeof(NTItemData));
		BackupStream.Write(&NewData, sizeof(NTItemData));
	}
}


void ItemDlg::OnBnClickedItemload()
{
	Release();
	NTDlgShortCut::pItemView->ClearDlg();
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
			memcpy_s(NewWeapon->Only, sizeof(NewWeapon->Only), NewItem->Only, sizeof(NewItem->Only));
			NewWeapon->Output = NewItem->Output;
			NewWeapon->Price = NewItem->Price;
			NewWeapon->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NewWeapon->WeaponType = (NTWeapon::WEAPONTYPE)NewItem->Type;
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
			memcpy_s(NewArmor->Only, sizeof(NewArmor->Only), NewItem->Only, sizeof(NewItem->Only));
			NewArmor->Output = NewItem->Output;
			NewArmor->Price = NewItem->Price;
			NewArmor->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
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
			memcpy_s(NewHelmet->Only, sizeof(NewHelmet->Only), NewItem->Only, sizeof(NewItem->Only));
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
			memcpy_s(NewAcc->Only, sizeof(NewAcc->Only), NewItem->Only, sizeof(NewItem->Only));
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
	TreeEquip = ItemTree.InsertItem(L"Equip");
	ItemTree.SetItemData(TreeEquip, (DWORD_PTR)nullptr);

	TreeWeapon = ItemTree.InsertItem(L"Weapon", TreeEquip);
	ItemTree.SetItemData(TreeWeapon, (DWORD_PTR)nullptr);
	TreeHelmet = ItemTree.InsertItem(L"Helmet", TreeEquip);
	ItemTree.SetItemData(TreeHelmet, (DWORD_PTR)nullptr);
	TreeArmor = ItemTree.InsertItem(L"Armor", TreeEquip);
	ItemTree.SetItemData(TreeArmor, (DWORD_PTR)nullptr);
	TreeAcc = ItemTree.InsertItem(L"Accessory", TreeEquip);
	ItemTree.SetItemData(TreeAcc, (DWORD_PTR)nullptr);
	ItemTree.Expand(TreeEquip, TVE_EXPAND);

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

HTREEITEM ItemDlg::Find(HTREEITEM _ITEM, DWORD_PTR _Data)
{
	if (_ITEM == nullptr)
	{
		_ITEM = ItemTree.GetRootItem();
	}

	if (ItemTree.GetItemData(_ITEM) == _Data)
	{
		return _ITEM;
	}
	else
	{
		HTREEITEM TmpITEM;
		TmpITEM = ItemTree.GetChildItem(_ITEM);
		if (TmpITEM != nullptr)
		{
			HTREEITEM ReturnItem = Find(TmpITEM, _Data);
			if (ReturnItem != nullptr)
			{
				return ReturnItem;
			}
		}

		HTREEITEM TempITEM;
		TempITEM = ItemTree.GetNextSiblingItem(_ITEM);
		if (TempITEM != nullptr)
		{
			HTREEITEM ReturnItem = Find(TempITEM, _Data);
			if (ReturnItem != nullptr)
			{
				return ReturnItem;
			}
		}
	}

	return nullptr;
}

void ItemDlg::UpdateName(HTREEITEM _ITEM)
{
	if (_ITEM == nullptr)
	{
		return;
	}
	ItemTree.SetItemText(_ITEM, ((NTItem*)ItemTree.GetItemData(_ITEM))->GetName());
}


void ItemDlg::OnTvnKeydownItemtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (VK_DELETE == pTVKeyDown->wVKey && nullptr != CurItem && ItemTree.GetItemData(CurItem) != (DWORD_PTR)nullptr)
	{
		NTItem* Tmp = (NTItem*)ItemTree.GetItemData(CurItem);

		if (Tmp != nullptr)
		{
			NTDlgShortCut::pItemView->ClearDlg();
			std::unordered_map<std::wstring, NTItem*>::iterator Find = ItemMap.find(Tmp->GetName());
			if (Find == ItemMap.end())
			{
				return;
			}
			delete Find->second;
			Find->second = nullptr;
			ItemMap.erase(Find);
		}

		ItemTree.DeleteItem(CurItem);
		ItemTree.SelectItem(nullptr);
	}
}
