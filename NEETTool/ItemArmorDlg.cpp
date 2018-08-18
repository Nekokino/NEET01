// ItemArmorDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemArmorDlg.h"
#include "afxdialogex.h"


// ItemArmorDlg ��ȭ �����Դϴ�.

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


// ItemArmorDlg �޽��� ó�����Դϴ�.


void ItemArmorDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemArmorDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemArmorDlg::OnEnChangeArmordef()
{
	UpdateData(TRUE);
	CurItem->Def = ArmorDef;
	UpdateData(FALSE);
}
