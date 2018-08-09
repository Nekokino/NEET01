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