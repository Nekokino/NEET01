#pragma once
#include "TabDlg.h"
#include "afxcmn.h"
#include "afxwin.h"


// ItemDlg ��ȭ �����Դϴ�.

class ItemDlg : public TabDlg
{
	DECLARE_DYNAMIC(ItemDlg)

public:
	ItemDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ItemDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ItemDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTvnSelchangedItemtree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeSelecttype();

	void InitDlg();
	CTreeCtrl ItemTree;
	HTREEITEM CurItem;
	virtual BOOL OnInitDialog();
	CComboBox TypeComBox;
	int CurBox;
};
