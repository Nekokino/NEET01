// ItemBaseDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemBaseDlg.h"
#include "afxdialogex.h"


// ItemBaseDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ItemBaseDlg, CDialogEx)

ItemBaseDlg::ItemBaseDlg(CWnd* pParent /*=NULL*/)
	: ItemEditDlg(IDD_ITEMBASEDLG, pParent)
{
	SizeY = 500;
}

ItemBaseDlg::~ItemBaseDlg()
{
}

void ItemBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ItemBaseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ItemBaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ItemBaseDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_ITEMNAME, &ItemBaseDlg::OnEnChangeItemname)
	ON_EN_CHANGE(IDC_ITEMPRICE, &ItemBaseDlg::OnEnChangeItemprice)
	ON_BN_CLICKED(IDC_ITEMSELLABLE, &ItemBaseDlg::OnBnClickedItemsellable)
	ON_EN_CHANGE(IDC_ITEMINFO, &ItemBaseDlg::OnEnChangeIteminfo)
	ON_EN_CHANGE(IDC_OUTPUTNAME, &ItemBaseDlg::OnEnChangeOutputname)
END_MESSAGE_MAP()


// ItemBaseDlg �޽��� ó�����Դϴ�.


void ItemBaseDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnEnChangeItemname()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// ItemEditDlg::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnEnChangeItemprice()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// ItemEditDlg::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnBnClickedItemsellable()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnEnChangeIteminfo()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// ItemEditDlg::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ItemBaseDlg::OnEnChangeOutputname()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// ItemEditDlg::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
