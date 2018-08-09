#pragma once
#include <list>

#include "ItemEditDlg.h"
#include <NTItem.h>


// ItemView 뷰입니다.

class ItemView : public CScrollView
{
	DECLARE_DYNCREATE(ItemView)

protected:
	ItemView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ItemView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

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


