#pragma once
#include "TabDlg.h"


// TextDlg ��ȭ �����Դϴ�.

class TextDlg : public TabDlg
{
	DECLARE_DYNAMIC(TextDlg)

public:
	TextDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TextDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
