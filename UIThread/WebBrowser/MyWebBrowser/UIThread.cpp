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

	CMyWebBrowserDlg dlg;

	if (dlg.Create(CMyWebBrowserDlg::IDD)) {

		dlg.ShowWindow( SW_HIDE );
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.RunModalLoop();
	}
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();

	//myWebDlg.Create(IDD_MYWEBBROWSER_DIALOG, NULL);

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
