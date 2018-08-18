// ItemArmorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemArmorDlg.h"
#include "afxdialogex.h"


// ItemArmorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ItemArmorDlg, CDialogEx)

ItemArmorDlg::ItemArmorDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMARMORDLG, pParent)
	, ArmorDef(0)
{
	SizeY = 100;
}

ItemArmorDlg::~ItemArmorDlg()
{
}

void ItemArmorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ARMORDEF, ArmorDef);
}


BEGIN_MESSAGE_MAP(ItemArmorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemArmorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemArmorDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_ARMORDEF, &ItemArmorDlg::OnEnChangeArmordef)
END_MESSAGE_MAP()


// ItemArmorDlg 메시지 처리기입니다.


void ItemArmorDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemArmorDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemArmorDlg::OnEnChangeArmordef()
{
	UpdateData(TRUE);
	CurItem->Def = ArmorDef;
	UpdateData(FALSE);
}
