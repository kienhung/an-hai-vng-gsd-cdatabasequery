// UIThread.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebBrowser.h"
#include "UIThread.h"
#include "MyWebBrowserDlg.h"

// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread()
{
}

CUIThread::~CUIThread()
{
}

BOOL CUIThread::InitInstance()
{
	if (dlg.Create(CMyWebBrowserDlg::IDD), CWnd::GetDesktopWindow()) {
		dlg.ShowWindow(SW_SHOW);
		m_pMainWnd = &dlg;
	}
	return TRUE;
}

int CUIThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
END_MESSAGE_MAP()


// CUIThread message handlers
