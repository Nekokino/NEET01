// MenuDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "ItemDlg.h"
#include "MapDlg.h"
#include "ResDlg.h"
#include "NTDlgShortCut.h"

#include <NTWinShortCut.h>
#include <NTSceneSystem.h>
#include <NTSpRenderer.h>



// MenuDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(MenuDlg, TabDlg)

MenuDlg::MenuDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_RIGHTMENU, pParent), CurIndex(0)
{
	NTDlgShortCut::pMenuDlg = this;
}

MenuDlg::~MenuDlg()
{
	for (size_t i = 0; i < DlgVec.size(); i++)
	{
		delete DlgVec[i];
	}
}

void MenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENUTAB, MenuTabCtrl);
}


BEGIN_MESSAGE_MAP(MenuDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MenuDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MenuDlg::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MENUTAB, &MenuDlg::OnTcnSelchangeMenutab)
END_MESSAGE_MAP()


// MenuDlg 메시지 처리기입니다.




void MenuDlg::OnBnClickedOk()
{
	
}


void MenuDlg::OnBnClickedCancel()
{
	
}


void MenuDlg::OnTcnSelchangeMenutab(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowDlg(MenuTabCtrl.GetCurSel());
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


BOOL MenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(RGB(0, 128, 128), TRUE);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void MenuDlg::ShowDlg(size_t _Index)
{
	DlgVec[CurIndex]->ShowWindow(SW_HIDE);
	DlgVec[_Index]->ShowWindow(SW_SHOW);
	MenuTabCtrl.SetCurSel((int)_Index);
	NTWinShortCut::GetMainSceneSystem().ChangeScene(DlgVec[_Index]->SceneName.GetString());
	CurIndex = _Index;
}

void MenuDlg::DlgInit()
{
	CreateDlg<ResDlg>(IDD_ResDlg, L"ResDlg");
	CreateDlg<TextDlg>(IDD_TEXTDLG, L"TextDlg");
	CreateDlg<ItemDlg>(IDD_ItemDlg, L"ItemDlg");
	CreateDlg<MapDlg>(IDD_MapDlg, L"MapDlg");
	ShowDlg(0);
}