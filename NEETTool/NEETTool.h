
// NEETTool.h : NEETTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNEETToolApp:
// �� Ŭ������ ������ ���ؼ��� NEETTool.cpp�� �����Ͻʽÿ�.
//

class CNEETToolApp : public CWinApp
{
public:
	CNEETToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CNEETToolApp theApp;
