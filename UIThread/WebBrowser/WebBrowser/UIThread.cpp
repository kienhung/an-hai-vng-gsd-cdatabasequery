// UIThread.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "UIThread.h"
#include "UIThreadDialog.h"

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
	CUIThreadDialog dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

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
