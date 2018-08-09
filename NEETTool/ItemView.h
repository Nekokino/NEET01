#pragma once
#include <list>

#include "ItemEditDlg.h"
#include <NTItem.h>


// ItemView ���Դϴ�.

class ItemView : public CScrollView
{
	DECLARE_DYNCREATE(ItemView)

protected:
	ItemView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~ItemView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
	

public:
	std::list<ItemEditDlg*>::iterator StartIter;
	std::list<ItemEditDlg*>::iterator EndIter;
	std::list<ItemEditDlg*> DlgList;

public:
	ItemEditDlg* CreateDlg(const type_info* _Type);


public:
	NTItem* CurItem;

	void ClearDlg();
	void SetItem(NTItem* _Item);
	void Reset();
};


