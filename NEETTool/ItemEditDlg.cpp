#include "stdafx.h"
#include "ItemEditDlg.h"

BOOL ItemEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(ItemEditDlg, CDialogEx)
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

void ItemEditDlg::OnNcPaint()
{

}