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
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_TIMER ()
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CMainDlg, CDialog)
END_EVENTSINK_MAP()

void CMainDlg::OnBnClickedButton1()
{
	//m_pNavigatingThread ->PostThreadMessage(ON_NAVIGATE, 0, 0);
	m_pNavigatingThread ->m_pMainWnd->PostMessage(ON_NAVIGATE);
}

BOOL CMainDlg:: OnInitDialog() {

	m_pNavigatingThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));
	TIMER_ID = 1;
	m_iCurrentIndex = 0;
	m_iFrameCount = 21;


	if (!SetTimer(TIMER_ID, 100, NULL)) {
		AfxMessageBox(L"Set Timer Fail", MB_ICONERROR);
	}
	return TRUE;
}


void CMainDlg::OnBnClickedButton2()
{



}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); 


	//RECT rect;
	//::GetClientRect(m_hWnd, &rect);
	//::FillRect(dc.m_hDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	CString strImagePath;


	TCHAR szModulePath[MAX_PATH]={0};
	GetModuleFileName(NULL,szModulePath,MAX_PATH);
	PathRemoveFileSpec(szModulePath);

	strImagePath.Format(L"%s\\Clock\\Frame%d.png", szModulePath, m_iCurrentIndex);
	
	Graphics graphics(dc.m_hDC);
	Image image(strImagePath);
	
	graphics.DrawImage(&image, 250, 220);
	graphics.DrawImage(&image, 350, 500);
}

void CMainDlg::OnTimer( UINT nTimerID )
{

	m_iCurrentIndex++;
	m_iCurrentIndex = m_iCurrentIndex%m_iFrameCount;
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

}
