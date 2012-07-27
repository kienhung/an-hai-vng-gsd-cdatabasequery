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

	CWinThread *m_pNavigatingThread;

	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnAfterInitDialog( WPARAM, LPARAM );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	CExplorer1 *m_explorer;

	DECLARE_EVENTSINK_MAP()
	afx_msg void OnPaint();
};
