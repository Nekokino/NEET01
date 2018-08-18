#pragma once
#include "ItemEditDlg.h"

#include <NTHelmet.h>


// ItemHelmetDlg ��ȭ �����Դϴ�.

class ItemHelmetDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemHelmetDlg)

public:
	ItemHelmetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ItemHelmetDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMHELMETDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	NTHelmet* CurItem;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int HelmetDef;
	afx_msg void OnEnChangeHelmetdef();

	void SetItemData(NTHelmet* _Item)
	{
		CurItem = _Item;
		UpdateData(TRUE);
		HelmetDef = _Item->Def;
		UpdateData(FALSE);
	}
};
