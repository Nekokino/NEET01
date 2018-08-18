#pragma once
#include "ItemEditDlg.h"
#include <NTWeapon.h>


// ItemWeaponDlg 대화 상자입니다.

class ItemWeaponDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemWeaponDlg)

public:
	ItemWeaponDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemWeaponDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMWEAPONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio(UINT _ID);

	NTWeapon* CurItem;
	int WeaponType;
	int WeaponATK;
	int WeaponCrit;

	void SetItemData(NTWeapon* _Item)
	{
		CurItem = _Item;
		UpdateData(TRUE);
		WeaponType = (int)_Item->WeaponType;
		WeaponATK = _Item->Atk;
		WeaponCrit = _Item->Crit;
		UpdateData(FALSE);
	}
	afx_msg void OnEnChangeWeaponcrit();
	afx_msg void OnEnChangeWeaponatk();
};
