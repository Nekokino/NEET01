#pragma once
#include "TabDlg.h"


// MapDlg ��ȭ �����Դϴ�.

class MapDlg : public TabDlg
{
	DECLARE_DYNAMIC(MapDlg)

public:
	MapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MapDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
