// MapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "MapDlg.h"
#include "afxdialogex.h"


// MapDlg ��ȭ �����Դϴ�.

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


// MapDlg �޽��� ó�����Դϴ�.


void MapDlg::OnBnClickedOk()
{
	
}


void MapDlg::OnBnClickedCancel()
{
	
}
