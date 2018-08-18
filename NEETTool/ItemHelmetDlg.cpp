// ItemHelmetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemHelmetDlg.h"
#include "afxdialogex.h"


// ItemHelmetDlg 대화 상자입니다.

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


// ItemHelmetDlg 메시지 처리기입니다.


void ItemHelmetDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemHelmetDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemHelmetDlg::OnEnChangeHelmetdef()
{
	UpdateData(TRUE);
	CurItem->Def = HelmetDef;
	UpdateData(FALSE);
}
