// ItemEquipDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemEquipDlg.h"
#include "afxdialogex.h"


// ItemEquipDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ItemEquipDlg, CDialogEx)

ItemEquipDlg::ItemEquipDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMEQUIPDLG, pParent)
	, AbleChrono(FALSE)
	, AbleLucca(FALSE)
	, AbleMaru(FALSE)
	, AbleKaeru(FALSE)
	, AbleRobo(FALSE)
	, AbleEira(FALSE)
	, AbleMaou(FALSE)
	, AbleSpecial(FALSE)
{
	SizeY = 150;
}

ItemEquipDlg::~ItemEquipDlg()
{
}

void ItemEquipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_USECHRONO, AbleChrono);
	DDX_Check(pDX, IDC_USELUCCA, AbleLucca);
	DDX_Check(pDX, IDC_USEMARU, AbleMaru);
	DDX_Check(pDX, IDC_USEKAERU, AbleKaeru);
	DDX_Check(pDX, IDC_USEROBO, AbleRobo);
	DDX_Check(pDX, IDC_USEEIRA, AbleEira);
	DDX_Check(pDX, IDC_USEMAOU, AbleMaou);
	DDX_Check(pDX, IDC_ITEMSPECIAL, AbleSpecial);
}


BEGIN_MESSAGE_MAP(ItemEquipDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemEquipDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemEquipDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_USECHRONO, &ItemEquipDlg::OnBnClickedUsechrono)
	ON_BN_CLICKED(IDC_USELUCCA, &ItemEquipDlg::OnBnClickedUselucca)
	ON_BN_CLICKED(IDC_USEMARU, &ItemEquipDlg::OnBnClickedUsemaru)
	ON_BN_CLICKED(IDC_USEKAERU, &ItemEquipDlg::OnBnClickedUsekaeru)
	ON_BN_CLICKED(IDC_USEROBO, &ItemEquipDlg::OnBnClickedUserobo)
	ON_BN_CLICKED(IDC_USEEIRA, &ItemEquipDlg::OnBnClickedUseeira)
	ON_BN_CLICKED(IDC_USEMAOU, &ItemEquipDlg::OnBnClickedUsemaou)
	ON_BN_CLICKED(IDC_ITEMSPECIAL, &ItemEquipDlg::OnBnClickedItemspecial)
END_MESSAGE_MAP()


// ItemEquipDlg 메시지 처리기입니다.


void ItemEquipDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemEquipDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ItemEquipDlg::OnBnClickedUsechrono()
{
	UpdateData(TRUE);
	if (AbleChrono == TRUE)
		CurItem->Only[CHRONO] = true;
	else
		CurItem->Only[CHRONO] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUselucca()
{
	UpdateData(TRUE);
	if (AbleLucca == TRUE)
		CurItem->Only[LUCCA] = true;
	else
		CurItem->Only[LUCCA] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUsemaru()
{
	UpdateData(TRUE);
	if (AbleMaru == TRUE)
		CurItem->Only[MARU] = true;
	else
		CurItem->Only[MARU] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUsekaeru()
{
	UpdateData(TRUE);
	if (AbleKaeru == TRUE)
		CurItem->Only[KAERU] = true;
	else
		CurItem->Only[KAERU] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUserobo()
{
	UpdateData(TRUE);
	if (AbleRobo == TRUE)
		CurItem->Only[ROBO] = true;
	else
		CurItem->Only[ROBO] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUseeira()
{
	UpdateData(TRUE);
	if (AbleEira == TRUE)
		CurItem->Only[EIRA] = true;
	else
		CurItem->Only[EIRA] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedUsemaou()
{
	UpdateData(TRUE);
	if (AbleMaou == TRUE)
		CurItem->Only[MAOU] = true;
	else
		CurItem->Only[MAOU] = false;
	UpdateData(FALSE);
}


void ItemEquipDlg::OnBnClickedItemspecial()
{
	UpdateData(TRUE);
	if (AbleSpecial == TRUE)
		CurItem->bSpecial = true;
	else
		CurItem->bSpecial = false;
	UpdateData(FALSE);
}
