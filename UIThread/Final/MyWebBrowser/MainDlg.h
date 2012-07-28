#pragma once
#include "MyWebBrowserDlg.h"
#include "explorer.h"

class CMainDlg : public CDialog
{
	//DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainDlg();

// Dialog Data
	enum { IDD = IDD_MAINDLG };

protected:

	int TIMER_ID;
	int m_iCurrentIndex;
	int m_iFrameCount;
	Image **m_ppImage;

	RECT m_rectBitmap;

	CWinThread *m_pNavigatingThread;

	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnDownloadComplete( WPARAM, LPARAM );
	afx_msg LRESULT OnDownloadBeginning( WPARAM, LPARAM );


	afx_msg void OnPaint();
	afx_msg void OnTimer (UINT nTimerID);

	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnBnClickedBtnNavigate();
};
