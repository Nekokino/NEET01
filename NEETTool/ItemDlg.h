#pragma once
#include "TabDlg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <unordered_map>
#include <NTItem.h>


// ItemDlg 대화 상자입니다.

class ItemDlg : public TabDlg
{
	DECLARE_DYNAMIC(ItemDlg)

public:
	ItemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ItemDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ItemDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTvnSelchangedItemtree(NMHDR *pNMHDR, LRESULT *pResult);

	void InitDlg();
	CTreeCtrl ItemTree;
	HTREEITEM CurItem;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCreateitem();


	std::unordered_map<std::wstring, Autoptr<NTItem>> ItemMap;

	template<typename T>
	void CreateItem()
	{
		NTItem* Item = new T();

		wchar_t Time[256] = {};
		_itow_s((int)time(nullptr), Time, 36);

		std::unordered_map<std::wstring, Autoptr<NTItem>>::iterator FindIter = ItemMap.find(Time);

		if (FindIter != ItemMap.end())
		{
			delete Item;
			return;
		}

		Item->SetName(L"키값입니다. 게임에는 띄우지 않을 확률이 높습니다.");
		Item->Output = L"게임에서 출력될 이름입니다.";
		Item->Info = L"아이템 설명란에 출력될 문자열입니다.";
		Item->Sellable = true;
		Item->Price = 1;

		ItemMap.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(Time, Item));

		HTREEITEM NewItem = ItemTree.InsertItem(Time, CurItem);
		ItemTree.SetItemData(NewItem, (DWORD_PTR)Item);
		ItemTree.Expand(CurItem, TVE_EXPAND);
	}
	afx_msg void OnBnClickedItemsave();
	afx_msg void OnBnClickedItemload();
};
