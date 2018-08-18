// ItemBaseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemBaseDlg.h"
#include "afxdialogex.h"

#include "NTDlgShortCut.h"


// ItemBaseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ItemBaseDlg, CDialogEx)

ItemBaseDlg::ItemBaseDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMBASEDLG, pParent)
	, ItemKey(_T(""))
	, ItemOutput(_T(""))
	, ItemSellable(FALSE)
	, ItemInfo(_T(""))
	, ItemPrice(0)
{
	SizeY = 450;
}

ItemBaseDlg::~ItemBaseDlg()
{
}

void ItemBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ITEMNAME, ItemKey);
	DDX_Text(pDX, IDC_OUTPUTNAME, ItemOutput);
	DDX_Check(pDX, IDC_ITEMSELLABLE, ItemSellable);
	DDX_Text(pDX, IDC_ITEMINFO, ItemInfo);
	DDX_Text(pDX, IDC_ITEMPRICE, ItemPrice);
}


BEGIN_MESSAGE_MAP(ItemBaseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemBaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemBaseDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_ITEMNAME, &ItemBaseDlg::OnEnChangeItemname)
	ON_EN_CHANGE(IDC_ITEMPRICE, &ItemBaseDlg::OnEnChangeItemprice)
	ON_BN_CLICKED(IDC_ITEMSELLABLE, &ItemBaseDlg::OnBnClickedItemsellable)
	ON_EN_CHANGE(IDC_ITEMINFO, &ItemBaseDlg::OnEnChangeIteminfo)
	ON_EN_CHANGE(IDC_OUTPUTNAME, &ItemBaseDlg::OnEnChangeOutputname)
END_MESSAGE_MAP()


// ItemBaseDlg 메시지 처리기입니다.


void ItemBaseDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnEnChangeItemname()
{
	UpdateData(TRUE);
	CurItem->SetName(ItemKey);
	NTDlgShortCut::pItemDlg->UpdateName(NTDlgShortCut::pItemDlg->Find(nullptr, (DWORD_PTR)CurItem));
	UpdateData(FALSE);
}


void ItemBaseDlg::OnEnChangeItemprice()
{
	UpdateData(TRUE);
	CurItem->Price = ItemPrice;
	UpdateData(FALSE);
}


void ItemBaseDlg::OnBnClickedItemsellable()
{
	UpdateData(TRUE);
	if (ItemSellable == TRUE)
	{
		CurItem->Sellable = true;
	}
	else
	{
		CurItem->Sellable = false;
	}
	UpdateData(FALSE);
}


void ItemBaseDlg::OnEnChangeIteminfo()
{
	UpdateData(TRUE);
	CurItem->Info = ItemInfo;
	UpdateData(FALSE);
}


void ItemBaseDlg::OnEnChangeOutputname()
{
	UpdateData(TRUE);
	CurItem->Output = ItemOutput;
	UpdateData(FALSE);
}