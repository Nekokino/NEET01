#include "stdafx.h"
#include "NTSplitWnd.h"


NTSplitWnd::NTSplitWnd() : ScrollLock(true)
{
}


NTSplitWnd::~NTSplitWnd()
{
}

BEGIN_MESSAGE_MAP(NTSplitWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void NTSplitWnd::OnLButtonDown(UINT _nFlags, CPoint _Point)
{
	if (ScrollLock == true)
	{
		return;
	}

	CSplitterWnd::OnLButtonDown(_nFlags, _Point);
}

void NTSplitWnd::OnMouseMove(UINT _nFlags, CPoint _Point)
{
	if (true == ScrollLock)
	{
		return;
	}

	CSplitterWnd::OnMouseMove(_nFlags, _Point);
}

BOOL NTSplitWnd::OnSetCursor(CWnd * _Wnd, UINT _nHitTest, UINT _Msg)
{
	if (true == ScrollLock)
	{
		return 0;
	}
	return CSplitterWnd::OnSetCursor(_Wnd, _nHitTest, _Msg);
}

BOOL NTSplitWnd::PreCreateWindow(CREATESTRUCT & cs)
{
	m_cxSplitter = 1;
	m_cySplitter = 1;

	m_cxSplitterGap = 1;

	return CSplitterWnd::PreCreateWindow(cs);
}