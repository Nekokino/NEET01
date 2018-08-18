// ItemHelmetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemHelmetDlg.h"
#include "afxdialogex.h"


// ItemHelmetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ItemHelmetDlg, CDialogEx)

ItemHelmetDlg::ItemHelmetDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMHELMETDLG, pParent)
	, HelmetDef(0)
{
	SizeY = 100;
}

ItemHelmetDlg::~ItemHelmetDlg()
{
}

void ItemHelmetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HELMETDEF, HelmetDef);
}


BEGIN_MESSAGE_MAP(ItemHelmetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemHelmetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemHelmetDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_HELMETDEF, &ItemHelmetDlg::OnEnChangeHelmetdef)
END_MESSAGE_MAP()


// ItemHelmetDlg �޽��� ó�����Դϴ�.


void ItemHelmetDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemHelmetDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemHelmetDlg::OnEnChangeHelmetdef()
{
	UpdateData(TRUE);
	CurItem->Def = HelmetDef;
	UpdateData(FALSE);
}
