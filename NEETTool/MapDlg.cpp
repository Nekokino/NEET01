// MapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "MapDlg.h"
#include "afxdialogex.h"


// MapDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(MapDlg, TabDlg)

MapDlg::MapDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_MapDlg, pParent)
{

}

MapDlg::~MapDlg()
{
}

void MapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MapDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MapDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// MapDlg 메시지 처리기입니다.


void MapDlg::OnBnClickedOk()
{
	
}


void MapDlg::OnBnClickedCancel()
{
	
}
