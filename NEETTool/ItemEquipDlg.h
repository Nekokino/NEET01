#pragma once
#include "ItemEditDlg.h"

#include <NTEquip.h>

// ItemEquipDlg 대화 상자입니다.

class ItemEquipDlg : public ItemEditDlg
{
	DECLARE_DYNAMIC(ItemEquipDlg)

public:
	ItemEquipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemEquipDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEMEQUIPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	NTEquip* CurItem;

	void SetItemData(NTEquip* _Item)
	{
		CurItem = _Item;
		UpdateData(TRUE);
		AbleChrono = _Item->Only[CHRONO];
		AbleLucca = _Item->Only[LUCCA];
		AbleMaru = _Item->Only[MARU];
		AbleKaeru = _Item->Only[KAERU];
		AbleRobo = _Item->Only[ROBO];
		AbleEira = _Item->Only[EIRA];
		AbleMaou = _Item->Only[MAOU];
		AbleSpecial = _Item->bSpecial;
		UpdateData(FALSE);
	}

	void SetOnly(int _Index)
	{
		UpdateData(TRUE);
		switch (_Index)
		{
		case 0:
			AbleChrono = FALSE;
			AbleLucca = FALSE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = TRUE;
			AbleEira = FALSE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = false;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = true;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = false;
			break;
		case 1:
			AbleChrono = FALSE;
			AbleLucca = TRUE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = FALSE;
			AbleEira = FALSE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = true;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = false;
			break;
		case 2:
			AbleChrono = FALSE;
			AbleLucca = FALSE;
			AbleMaru = FALSE;
			AbleKaeru = TRUE;
			AbleRobo = FALSE;
			AbleEira = FALSE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = false;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = true;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = false;
			break;
		case 3:
			AbleChrono = FALSE;
			AbleLucca = FALSE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = FALSE;
			AbleEira = TRUE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = false;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = true;
			CurItem->Only[MAOU] = false;
			break;
		case 4:
			AbleChrono = FALSE;
			AbleLucca = TRUE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = FALSE;
			AbleEira = FALSE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = true;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = false;
			break;
		case 5:
			AbleChrono = FALSE;
			AbleLucca = FALSE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = FALSE;
			AbleEira = FALSE;
			AbleMaou = TRUE;
			CurItem->Only[CHRONO] = false;
			CurItem->Only[LUCCA] = false;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = true;
			break;
		case 6:
			AbleChrono = TRUE;
			AbleLucca = FALSE;
			AbleMaru = FALSE;
			AbleKaeru = FALSE;
			AbleRobo = FALSE;
			AbleEira = FALSE;
			AbleMaou = FALSE;
			CurItem->Only[CHRONO] = true;
			CurItem->Only[LUCCA] = false;
			CurItem->Only[MARU] = false;
			CurItem->Only[KAERU] = false;
			CurItem->Only[ROBO] = false;
			CurItem->Only[EIRA] = false;
			CurItem->Only[MAOU] = false;
			break;
		default:
			break;
		}
		UpdateData(FALSE);
	}
	afx_msg void OnBnClickedUsechrono();
	afx_msg void OnBnClickedUselucca();
	afx_msg void OnBnClickedUsemaru();
	afx_msg void OnBnClickedUsekaeru();
	afx_msg void OnBnClickedUserobo();
	afx_msg void OnBnClickedUseeira();
	afx_msg void OnBnClickedUsemaou();
	afx_msg void OnBnClickedItemspecial();

	BOOL AbleChrono;
	BOOL AbleLucca;
	BOOL AbleMaru;
	BOOL AbleKaeru;
	BOOL AbleRobo;
	BOOL AbleEira;
	BOOL AbleMaou;
	BOOL AbleSpecial;
};
