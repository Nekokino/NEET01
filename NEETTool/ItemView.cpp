// ItemView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemView.h"

#include "NTDlgShortCut.h"
#include "ItemBaseDlg.h"
#include "ItemEquipDlg.h"
#include "ItemWeaponDlg.h"
#include "ItemArmorDlg.h"
#include "ItemHelmetDlg.h"


// ItemView

IMPLEMENT_DYNCREATE(ItemView, CScrollView)

ItemView::ItemView()
{
	NTDlgShortCut::pItemView = this;
}

ItemView::~ItemView()
{
	ClearDlg();
}


BEGIN_MESSAGE_MAP(ItemView, CScrollView)
END_MESSAGE_MAP()


// ItemView 그리기입니다.

void ItemView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

ItemEditDlg * ItemView::CreateDlg(const type_info * _Type)
{
	return nullptr;
}

void ItemView::ClearDlg()
{
	StartIter = DlgList.begin();
	EndIter = DlgList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			if (nullptr != (*StartIter)->m_hWnd)
			{
				(*StartIter)->ShowWindow(SW_HIDE);
			}
			delete (*StartIter);
		}
	}

	DlgList.clear();
}

void ItemView::SetItem(NTItem * _Item)
{
	CurItem = _Item;

	Reset();
}

void ItemView::Reset()
{
	POINT Pos = { 0 ,0 };
	POINT Size = { 640 , 0 };

	ItemBaseDlg* BaseDlg = new ItemBaseDlg();
	BaseDlg->Create(IDD_ITEMBASEDLG, this);
	BaseDlg->ShowWindow(SW_SHOW); 
	BaseDlg->SetWindowPos(this, Pos.x, Pos.y, Size.x, BaseDlg->SizeY, SWP_NOZORDER);
	BaseDlg->SetItemData(CurItem);
	Pos.y += BaseDlg->SizeY;
	DlgList.push_back(BaseDlg);

	const type_info* Type = CurItem->GetType();
	const char* TypeName = Type->name();
	if (strcmp(TypeName, "class NTWeapon") == 0 || strcmp(TypeName, "class NTArmor") == 0 || strcmp(TypeName, "class NTHelmet") == 0 || strcmp(TypeName, "class NTAcc") == 0)
	{
		ItemEquipDlg* EquipDlg = new ItemEquipDlg();
		EquipDlg->Create(IDD_ITEMEQUIPDLG, this);
		EquipDlg->ShowWindow(SW_SHOW);
		EquipDlg->SetWindowPos(this, Pos.x, Pos.y, Size.x, EquipDlg->SizeY, SWP_NOZORDER);
		EquipDlg->SetItemData((NTEquip*)CurItem);
		Pos.y += EquipDlg->SizeY;
		DlgList.push_back(EquipDlg);
	}

	if (strcmp(TypeName, "class NTWeapon") == 0)
	{
		ItemWeaponDlg* WeaponDlg = new ItemWeaponDlg();
		WeaponDlg->Create(IDD_ITEMWEAPONDLG, this);
		WeaponDlg->ShowWindow(SW_SHOW);
		WeaponDlg->SetWindowPos(this, Pos.x, Pos.y, Size.x, WeaponDlg->SizeY, SWP_NOZORDER);
		WeaponDlg->SetItemData((NTWeapon*)CurItem);
		Pos.y += WeaponDlg->SizeY;
		DlgList.push_back(WeaponDlg);
	}

	if (strcmp(TypeName, "class NTArmor") == 0)
	{
		ItemArmorDlg* ArmorDlg = new ItemArmorDlg();
		ArmorDlg->Create(IDD_ITEMARMORDLG, this);
		ArmorDlg->ShowWindow(SW_SHOW);
		ArmorDlg->SetWindowPos(this, Pos.x, Pos.y, Size.x, ArmorDlg->SizeY, SWP_NOZORDER);
		ArmorDlg->SetItemData((NTArmor*)CurItem);
		Pos.y += ArmorDlg->SizeY;
		DlgList.push_back(ArmorDlg);
	}

	if (strcmp(TypeName, "class NTHelmet") == 0)
	{
		ItemHelmetDlg* HelmetDlg = new ItemHelmetDlg();
		HelmetDlg->Create(IDD_ITEMHELMETDLG, this);
		HelmetDlg->ShowWindow(SW_SHOW);
		HelmetDlg->SetWindowPos(this, Pos.x, Pos.y, Size.x, HelmetDlg->SizeY, SWP_NOZORDER);
		HelmetDlg->SetItemData((NTHelmet*)CurItem);
		Pos.y += HelmetDlg->SizeY;
		DlgList.push_back(HelmetDlg);
	}

	SIZE SizeTotal;

	SizeTotal.cx = Size.x;
	SizeTotal.cy = Pos.y;
	SetScrollSizes(MM_TEXT, SizeTotal);
}

void ItemView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// ItemView 진단입니다.

#ifdef _DEBUG
void ItemView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void ItemView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// ItemView 메시지 처리기입니다.
