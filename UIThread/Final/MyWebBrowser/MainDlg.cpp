// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebBrowser.h"
#include "MainDlg.h"
#include "UIThread.h"



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{

}

CMainDlg::~CMainDlg()
{
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_MESSAGE(ON_WM_AFTERINIT, OnAfterInitDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CMainDlg, CDialog)
END_EVENTSINK_MAP()

void CMainDlg::OnBnClickedButton1()
{

}

BOOL CMainDlg:: OnInitDialog() {

	PostMessage(ON_WM_AFTERINIT);

	return TRUE;
}

LRESULT CMainDlg::OnAfterInitDialog( WPARAM, LPARAM ) {

	m_pNavigatingThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));
	return 0;
}
void CMainDlg::OnBnClickedButton2()
{



}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); 


	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	::FillRect(dc.m_hDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

}
