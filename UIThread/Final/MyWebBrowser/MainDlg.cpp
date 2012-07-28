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
	for (int i = 0; i < m_iFrameCount; i++) {
		delete m_ppImage[i];
		m_ppImage[i] = NULL;
	}
	delete []m_ppImage;
	m_ppImage = NULL;
}



BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER ()
	ON_MESSAGE(WM_DOWNLOADCOMPLETE, OnDownloadComplete)
	ON_MESSAGE(WM_DOWNLOADBEGINNING, OnDownloadBeginning)
	ON_BN_CLICKED(IDC_BTN_NAVIGATE, &CMainDlg::OnBnClickedBtnNavigate)
END_MESSAGE_MAP()



BOOL CMainDlg:: OnInitDialog() {

	m_pNavigatingThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));

	TIMER_ID = 1;
	m_iCurrentIndex = 0;
	m_iFrameCount = 21;

	m_rectBitmap.left = 350;
	m_rectBitmap.top = 500;


	m_ppImage = new Image*[m_iFrameCount];

	TCHAR szModulePath[MAX_PATH]={0};
	GetModuleFileName(NULL,szModulePath,MAX_PATH);
	PathRemoveFileSpec(szModulePath);

	for (int i = 0 ; i < m_iFrameCount; i++) {

		CString strImagePath;
		strImagePath.Format(L"%s\\Clock\\Frame%d.png", szModulePath, i);

		m_ppImage[i] = new Image( strImagePath);

		if (m_ppImage[i] != NULL && i == 0) {
			m_rectBitmap.right = m_rectBitmap.left + m_ppImage[i]->GetWidth();
			m_rectBitmap.bottom = m_rectBitmap.top + m_ppImage[i]->GetHeight();
		}
	}


	return TRUE;
}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); 

	Graphics graphics(dc.m_hDC);
	graphics.DrawImage(m_ppImage[m_iCurrentIndex], m_rectBitmap.left, m_rectBitmap.top);

}

void CMainDlg::OnTimer( UINT nTimerID )
{
	m_iCurrentIndex++;
	m_iCurrentIndex = m_iCurrentIndex%m_iFrameCount;

	InvalidateRect(&m_rectBitmap, FALSE);
}

LRESULT CMainDlg::OnDownloadComplete( WPARAM, LPARAM )
{
	KillTimer(TIMER_ID);
	return 0;
}

LRESULT CMainDlg::OnDownloadBeginning( WPARAM, LPARAM )
{
	if (!SetTimer(TIMER_ID, 150, NULL)) {
		AfxMessageBox(L"Set Timer Fail", MB_ICONERROR);
	}
	return 0;
}


void CMainDlg::OnBnClickedBtnNavigate()
{
	m_pNavigatingThread ->m_pMainWnd->PostMessage(ON_NAVIGATE);
}
