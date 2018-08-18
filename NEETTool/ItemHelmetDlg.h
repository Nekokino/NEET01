#pragma once
#include "ItemEditDlg.h"

#include <NTHelmet.h>


// ItemHelmetDlg 대화 상자입니다.

class ItemHelmetDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemHelmetDlg)

public:
	ItemHelmetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemHelmetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMHELMETDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
