
// MyWebBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebBrowser.h"
#include "MyWebBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyWebBrowserDlg::CMyWebBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyWebBrowserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



BEGIN_MESSAGE_MAP(CMyWebBrowserDlg, CDialog)
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(ON_NAVIGATE, OnNavigate)
	ON_WM_PAINT()
END_MESSAGE_MAP()




BOOL CMyWebBrowserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	m_pExplorer = (CExplorer1*)GetDlgItem(IDC_EXPLORER);
	m_pExplorer->Navigate(L"asus.com", NULL, NULL, NULL, NULL);
	return TRUE; 
}


HCURSOR CMyWebBrowserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMyWebBrowserDlg, CDialog)
	ON_EVENT(CMyWebBrowserDlg, IDC_EXPLORER, 259, CMyWebBrowserDlg::DocumentCompleteExplorer, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()



LRESULT CMyWebBrowserDlg::OnNavigate( WPARAM, LPARAM ) {
	//m_pExplorer->Navigate(L"asus.com", NULL, NULL, NULL, NULL);
	return 0;
}




BOOL CMyWebBrowserDlg::PreTranslateMessage( MSG* pMsg) {

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) {
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}



void CMyWebBrowserDlg::OnPaint()
{
	CPaintDC dc(this); 

	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	::FillRect(dc.m_hDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
}

void CMyWebBrowserDlg::DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL)
{
	ShowWindow(SW_SHOW);
}
