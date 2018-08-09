// ItemView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "ItemView.h"

#include "NTDlgShortCut.h"
#include "ItemBaseDlg.h"


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


// ItemView �׸����Դϴ�.

void ItemView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
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
	Pos.y += BaseDlg->SizeY;
	DlgList.push_back(BaseDlg);

	SIZE SizeTotal;

	SizeTotal.cx = Size.x;
	SizeTotal.cy = Pos.y;
	SetScrollSizes(MM_TEXT, SizeTotal);
}

void ItemView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// ItemView �����Դϴ�.

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


// ItemView �޽��� ó�����Դϴ�.
