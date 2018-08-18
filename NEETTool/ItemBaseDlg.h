#pragma once
#include "ItemEditDlg.h"
#include <NTItem.h>

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

	NTItem* CurItem;
	CString ItemKey;
	CString ItemOutput;
	BOOL ItemSellable;
	CString ItemInfo;
	int ItemPrice;

	void SetItemData(NTItem* _Item)
	{
		CurItem = _Item;
		const type_info* Type = _Item->GetType();
		const char* TypeName = Type->name();
		UpdateData(TRUE);
		ItemKey = CurItem->GetName();
		ItemOutput = CurItem->Output.c_str();
		ItemInfo = CurItem->Info.c_str();
		if (strcmp(TypeName, "class NTKeyItem") == 0)
		{
			CurItem->Price = 1;
			CurItem->Sellable = false;
		}
		ItemPrice = CurItem->Price;
		ItemSellable = CurItem->Sellable;
		UpdateData(FALSE);
	}
};
