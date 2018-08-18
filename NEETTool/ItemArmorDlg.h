#pragma once
#include "ItemEditDlg.h"

#include <NTArmor.h>


// ItemArmorDlg ��ȭ �����Դϴ�.

class ItemArmorDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemArmorDlg)

public:
	ItemArmorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ItemArmorDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMARMORDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
