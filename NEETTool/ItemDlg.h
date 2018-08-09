#pragma once
#include "TabDlg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <unordered_map>
#include <NTItem.h>


// ItemDlg ��ȭ �����Դϴ�.

class ItemDlg : public TabDlg
{
	DECLARE_DYNAMIC(ItemDlg)

public:
	ItemDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ItemDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ItemDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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


	std::unordered_map<std::wstring, NTItem*> ItemMap;

	template<typename T>
	void CreateItem()
	{
		NTItem* Item = new T();

		wchar_t Time[256] = {};
		_itow_s((int)time(nullptr), Time, 36);

		std::unordered_map<std::wstring, NTItem*>::iterator FindIter = ItemMap.find(Time);

		if (FindIter != ItemMap.end())
		{
			delete Item;
			return;
		}

		Item->SetName(L"Ű���Դϴ�. ���ӿ��� ����� ���� Ȯ���� �����ϴ�.");
		Item->Output = L"���ӿ��� ��µ� �̸��Դϴ�.";
		Item->Info = L"������ ������� ��µ� ���ڿ��Դϴ�.";
		Item->Sellable = true;
		Item->Price = 1;

		ItemMap.insert(std::unordered_map<std::wstring, NTItem*>::value_type(Time, Item));

		HTREEITEM NewItem = ItemTree.InsertItem(Time, CurItem);
		ItemTree.SetItemData(NewItem, (DWORD_PTR)Item);
		ItemTree.Expand(CurItem, TVE_EXPAND);
	}
	afx_msg void OnBnClickedItemsave();
	afx_msg void OnBnClickedItemload();

	void SetBaseTree();
	void Release();

};
