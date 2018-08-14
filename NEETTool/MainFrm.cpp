
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "NEETTool.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "RightView.h"

#include <WinCore.h>
#include "ToolBuilder.h"
#include "NTDlgShortCut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������� Ŭ���̾�Ʈ ������ �����ϴ� �並 ����ϴ�.
	/*if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("�� â�� ������ ���߽��ϴ�.\n");
		return -1;
	}*/

	MainWnd.Unlock();

	MainWnd.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE);

	MainWnd.CreateView(0, 0, RUNTIME_CLASS(LeftView), SIZE{ /*1024, 896*/100, 100 }, nullptr);
	MainWnd.CreateView(0, 1, RUNTIME_CLASS(RightView), SIZE{ 500, 896 }, nullptr);

	CWnd* Wnd = MainWnd.GetPane(0, 0);

	WinCore::Start<ToolBuilder>(AfxGetInstanceHandle(), L"ToolMainWindow", Wnd->m_hWnd);

	RECT Tmp = { 0, 0, 1024, 896 };

	AdjustWindowRect(&Tmp, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(nullptr, 0, 0, 2200, Tmp.bottom - Tmp.top + MainWnd.GetBorderY() * 2, SWP_NOMOVE | SWP_NOZORDER);
	
	NTDlgShortCut::pMenuDlg->DlgInit();
	NTDlgShortCut::pResDlg->InitResDlg();
	NTDlgShortCut::pTextDlg->InitDlg();
	NTDlgShortCut::pItemDlg->InitDlg();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	cs.hMenu = nullptr;
	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// �� â���� ��Ŀ���� �̵��մϴ�.
	MainWnd.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// �信�� ù° ũ���� �ش� ��ɿ� ��Ÿ������ �մϴ�.
	/*if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;*/

	//if (MainWnd.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//{
	//	return TRUE;
	//}

	// �׷��� ������ �⺻ ó���մϴ�.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

