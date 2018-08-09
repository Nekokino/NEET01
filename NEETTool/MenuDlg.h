#pragma once
#include <vector>
#include "afxcmn.h"
#include <NTScene.h>
#include <NTWinShortCut.h>
#include "TabDlg.h"

// MenuDlg 대화 상자입니다.

class MenuDlg : public TabDlg
{
	DECLARE_DYNAMIC(MenuDlg)

public:
	MenuDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MenuDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RIGHTMENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl MenuTabCtrl;

	size_t CurIndex;

private:
	std::vector<TabDlg*> DlgVec;

	template<typename T>
	void CreateDlg(UINT _DlgID, CString _ItemName)
	{
		UpdateData(TRUE);

		RECT tmp;
		MenuTabCtrl.GetClientRect(&tmp);
		MenuTabCtrl.InsertItem((int)DlgVec.size(), _ItemName);

		T* Dlg = new T();
		Dlg->SceneName = _ItemName;
		Dlg->Create(_DlgID, this);
		Dlg->SetBackgroundColor(RGB(255, 255, 255), TRUE);
		Dlg->SetWindowPos(nullptr, 18, 40, tmp.right - 18, tmp.bottom - 40, SWP_NOZORDER);

		DlgVec.push_back(Dlg);

		Autoptr<NTScene> Scene = NTWinShortCut::GetMainSceneSystem().FindScene(_ItemName.GetString());
		if (nullptr == Scene)
		{
			Scene = NTWinShortCut::GetMainSceneSystem().CreateScene(_ItemName.GetString());
			Autoptr<NTObject> Camera = Scene->CreateObject(L"DefaultCamera", 0);
			Autoptr<NTCamera> CameraCom = Camera->AddComponent<NTCamera>();
			CameraCom->PushRenderLayer(0, 1, 2, 3, 4);
		}

		UpdateData(FALSE);
	}

	void ShowDlg(size_t _Index);

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTcnSelchangeMenutab(NMHDR *pNMHDR, LRESULT *pResult);
	
	void DlgInit();
};
