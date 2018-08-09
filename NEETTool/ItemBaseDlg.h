#pragma once
#include "ItemEditDlg.h"

// ItemBaseDlg ��ȭ �����Դϴ�.

class ItemBaseDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemBaseDlg)

public:
	ItemBaseDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ItemBaseDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMBASEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeItemname();
	afx_msg void OnEnChangeItemprice();
	afx_msg void OnBnClickedItemsellable();
	afx_msg void OnEnChangeIteminfo();
	afx_msg void OnEnChangeOutputname();
};
