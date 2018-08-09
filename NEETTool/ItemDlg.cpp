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

#include "ItemView.h"
#include "NTDlgShortCut.h"


// ItemDlg 대화 상자입니다.

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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CCreateContext Context;

	Context.m_pNewViewClass = RUNTIME_CLASS(ItemView);

	ItemView* View = (ItemView*)((CFrameWnd*)this)->CreateView(&Context);

	RECT ViewSize = { 300, 18, 950, 750 };
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

		if (strcmp(TypeName, "class NTWeapon") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeName, "class NTArmor") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeName, "class NTHelmet") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeName, "class NTAcc") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeName, "class NTConsume") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeName, "class NTKeyItem") == 0)
		{
			int a = 0;
		}
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

		if (strcmp(TypeNameBuf, "class NTWeapon") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeNameBuf, "class NTArmor") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeNameBuf, "class NTHelmet") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeNameBuf, "class NTAcc") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeNameBuf, "class NTConsume") == 0)
		{
			int a = 0;
		}

		if (strcmp(TypeNameBuf, "class NTKeyItem") == 0)
		{
			int a = 0;
		}
	}

}

void ItemDlg::SetBaseTree()
{
	HTREEITEM Equip = ItemTree.InsertItem(L"Equip");
	ItemTree.SetItemData(Equip, (DWORD_PTR)nullptr);

	HTREEITEM Tmp = ItemTree.InsertItem(L"Weapon", Equip);
	ItemTree.SetItemData(Tmp, (DWORD_PTR)nullptr);
	Tmp = ItemTree.InsertItem(L"Helmet", Equip);
	ItemTree.SetItemData(Tmp, (DWORD_PTR)nullptr);
	Tmp = ItemTree.InsertItem(L"Armor", Equip);
	ItemTree.SetItemData(Tmp, (DWORD_PTR)nullptr);
	Tmp = ItemTree.InsertItem(L"Accessory", Equip);
	ItemTree.SetItemData(Tmp, (DWORD_PTR)nullptr);
	ItemTree.Expand(Equip, TVE_EXPAND);

	ItemTree.InsertItem(L"Consumable");
	ItemTree.InsertItem(L"KeyItem");
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
