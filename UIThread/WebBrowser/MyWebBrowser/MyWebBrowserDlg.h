
// MyWebBrowserDlg.h : header file
//

#pragma once
#include "Explorer.h"


// CMyWebBrowserDlg dialog
class CMyWebBrowserDlg : public CDialog
{
// Construction
public:
	CMyWebBrowserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYWEBBROWSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_explorer;
	DECLARE_EVENTSINK_MAP()
//	void DownloadCompleteExplorer1();
//	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
//	void NavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT* URL);
	void DownloadCompleteExplorer1();
};
