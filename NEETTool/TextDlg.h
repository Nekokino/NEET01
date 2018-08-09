#pragma once
#include "TabDlg.h"


// TextDlg 대화 상자입니다.

class TextDlg : public TabDlg
{
	DECLARE_DYNAMIC(TextDlg)

public:
	TextDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TextDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeUserindex();
	afx_msg void OnBnClickedSavetext();
	afx_msg void OnBnClickedLoadtext();
	afx_msg void OnEnChangeUsertext();

	void InitDlg();
	CString UserText;
	CString CurText;
	CString CurIndex;
	CString UserIndex;
	int CurTextIndex;
};
