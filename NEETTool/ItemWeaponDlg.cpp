// ItemWeaponDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemWeaponDlg.h"
#include "afxdialogex.h"

#include "NTDlgShortCut.h"
#include "ItemEquipDlg.h"


// ItemWeaponDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ItemWeaponDlg, CDialogEx)

ItemWeaponDlg::ItemWeaponDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMWEAPONDLG, pParent)
	, WeaponType(0)
	, WeaponATK(0)
	, WeaponCrit(0)
{
	SizeY = 170;
}

ItemWeaponDlg::~ItemWeaponDlg()
{
}

void ItemWeaponDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_WARM, WeaponType);
	DDX_Text(pDX, IDC_WEAPONATK, WeaponATK);
	DDX_Text(pDX, IDC_WEAPONCRIT, WeaponCrit);
	DDV_MinMaxInt(pDX, WeaponCrit, 0, 100);
}


BEGIN_MESSAGE_MAP(ItemWeaponDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemWeaponDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemWeaponDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_WARM, IDC_WSWORD, OnBnClickedRadio)
	ON_EN_CHANGE(IDC_WEAPONCRIT, &ItemWeaponDlg::OnEnChangeWeaponcrit)
	ON_EN_CHANGE(IDC_WEAPONATK, &ItemWeaponDlg::OnEnChangeWeaponatk)
END_MESSAGE_MAP()


// ItemWeaponDlg �޽��� ó�����Դϴ�.


void ItemWeaponDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemWeaponDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void ItemWeaponDlg::OnBnClickedRadio(UINT _ID)
{
	UpdateData(TRUE);
	CurItem->WeaponType = (NTWeapon::WEAPONTYPE)WeaponType;
	std::list<ItemEditDlg*>::iterator StartIter = NTDlgShortCut::pItemView->DlgList.begin();
	std::list<ItemEditDlg*>::iterator EndIter = NTDlgShortCut::pItemView->DlgList.end();
	ItemEquipDlg* Tmp = nullptr;
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == this)
		{
			--StartIter;
			Tmp = (ItemEquipDlg*)(*StartIter);
			break;
		}
	}
	Tmp->SetOnly(WeaponType);
	UpdateData(FALSE);
}



void ItemWeaponDlg::OnEnChangeWeaponcrit()
{
	UpdateData(TRUE);
	CurItem->Crit = WeaponCrit;
	UpdateData(FALSE);
}


void ItemWeaponDlg::OnEnChangeWeaponatk()
{
	UpdateData(TRUE);
	CurItem->Atk = WeaponATK;
	UpdateData(FALSE);
}
