#pragma once
#include "TabDlg.h"
#include "afxcmn.h"
#include "afxwin.h"


// ItemDlg 대화 상자입니다.

class ItemDlg : public TabDlg
{
	DECLARE_DYNAMIC(ItemDlg)

public:
	ItemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ItemDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
