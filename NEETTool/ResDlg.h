#pragma once
#include "afxcmn.h"

#include "afxwin.h"

#include "TabDlg.h"

#include <DirectHeader.h>
#include <NTSpRenderer.h>
#include <NTSpriteData.h>

#include <map>

// ResDlg 대화 상자입니다.

class ResDlg : public TabDlg
{
	DECLARE_DYNAMIC(ResDlg)

public:
	ResDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ResDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ResDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	Autoptr<NTSpRenderer> DefaultRenderer;

	CTreeCtrl ResTree;
	CString SpriteName;
	

	void InitResDlg();
	void GetResource(const wchar_t* _Path, HTREEITEM _ParentItem);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTvnSelchangedRestree(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int SliderValue;
	
	afx_msg void OnEnChangeMagni();
	CEdit MagniCtrl;
	CString ZoomX;
	float ZoomSize;
	CString ASD;
	HTREEITEM CurItem;

	std::unordered_map<std::wstring, NTSpriteData*> DataMap;

	afx_msg void OnEnChangeUsercutx();
	afx_msg void OnEnChangeUsercuty();
	afx_msg void OnDestroy();
	CString UserCutX;
	CString UserCutY;
	CString ItemCutX;
	CString ItemCutY;
	CString Index;
	UINT CurItemCutX;
	UINT CurItemCutY;
	afx_msg void OnBnClickedSavebutton();
	afx_msg void OnBnClickedLoadbutton();

	void Release();
	afx_msg void OnEnChangeIndex();
	
};
