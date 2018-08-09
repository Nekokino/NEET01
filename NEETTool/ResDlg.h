#pragma once
#include "afxcmn.h"

#include "afxwin.h"

#include "TabDlg.h"

#include <DirectHeader.h>
#include <NTSpRenderer.h>
#include <NTSpriteData.h>

#include <map>

// ResDlg ��ȭ �����Դϴ�.

class ResDlg : public TabDlg
{
	DECLARE_DYNAMIC(ResDlg)

public:
	ResDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ResDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ResDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
