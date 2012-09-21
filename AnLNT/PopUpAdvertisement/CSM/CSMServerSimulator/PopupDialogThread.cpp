// PopupDialogThread.cpp : implementation file
//

#include "stdafx.h"
#include "CSMServerSimulator.h"
#include "PopupDialogThread.h"
#include "PopupDlg.h"

// CPopupDialogThread

IMPLEMENT_DYNCREATE(CPopupDialogThread, CWinThread)

CPopupDialogThread::CPopupDialogThread()
{
}

CPopupDialogThread::~CPopupDialogThread()
{
}

BOOL CPopupDialogThread::InitInstance()
{
	if (m_popupDialog.Create(CPopupDlg::IDD)) {

		m_popupDialog.ShowWindow(SW_SHOW);
		m_pMainWnd = &m_popupDialog;
	}

	return TRUE;
}

int CPopupDialogThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPopupDialogThread, CWinThread)
END_MESSAGE_MAP()


// CPopupDialogThread message handlers
