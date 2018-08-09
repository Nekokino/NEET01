// ItemBaseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemBaseDlg.h"
#include "afxdialogex.h"


// ItemBaseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ItemBaseDlg, CDialogEx)

ItemBaseDlg::ItemBaseDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMBASEDLG, pParent)
{
	SizeY = 500;
}

ItemBaseDlg::~ItemBaseDlg()
{
}

void ItemBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// ItemEditDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnEnChangeItemprice()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// ItemEditDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnBnClickedItemsellable()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnEnChangeIteminfo()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// ItemEditDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemBaseDlg::OnEnChangeOutputname()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// ItemEditDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
