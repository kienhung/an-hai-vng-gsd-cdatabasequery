// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebBrowser.h"
#include "MainDlg.h"
#include "UIThread.h"

// CMainDlg dialog

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMainDlg message handlers

void CMainDlg::OnBnClickedButton1()
{
	AfxBeginThread(RUNTIME_CLASS(CUIThread));
}
