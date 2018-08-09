#pragma once

class ItemEditDlg : public CDialogEx
{
public:
	UINT SizeY;

public:
	ItemEditDlg(int _id, CWnd* _pWnd) : CDialogEx(_id, _pWnd)
	{

	}
	~ItemEditDlg() {}

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcPaint();
};

