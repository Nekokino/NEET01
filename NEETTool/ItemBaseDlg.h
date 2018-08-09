#pragma once
#include "ItemEditDlg.h"

// ItemBaseDlg 대화 상자입니다.

class ItemBaseDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemBaseDlg)

public:
	ItemBaseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemBaseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMBASEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeItemname();
	afx_msg void OnEnChangeItemprice();
	afx_msg void OnBnClickedItemsellable();
	afx_msg void OnEnChangeIteminfo();
	afx_msg void OnEnChangeOutputname();

	int gitTest;
};
