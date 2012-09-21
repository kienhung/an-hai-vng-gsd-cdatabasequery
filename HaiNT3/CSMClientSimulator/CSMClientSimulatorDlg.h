// CSMClientSimulatorDlg.h : header file
//

#pragma once
#include "WebHistory.h"


// CCSMClientSimulatorDlg dialog
class CCSMClientSimulatorDlg : public CDialog
{
// Construction
public:
	CCSMClientSimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSMCLIENTSIMULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;
	CWebHistory m_webHistoryFirefox;
	CWebHistory m_webHistoryChrome;

	
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnAsyncSocketNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
