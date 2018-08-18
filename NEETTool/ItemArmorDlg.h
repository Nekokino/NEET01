#pragma once
#include "ItemEditDlg.h"

#include <NTArmor.h>


// ItemArmorDlg 대화 상자입니다.

class ItemArmorDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemArmorDlg)

public:
	ItemArmorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemArmorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMARMORDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	NTArmor* CurItem;
	afx_msg void OnEnChangeArmordef();
	int ArmorDef;

	void SetItemData(NTArmor* _Item)
	{
		CurItem = _Item;
		UpdateData(TRUE);
		ArmorDef = _Item->Def;
		UpdateData(FALSE);
	}
};
