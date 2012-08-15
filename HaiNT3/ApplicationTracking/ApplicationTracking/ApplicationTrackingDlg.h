
// ApplicationTrackingDlg.h : header file
//

#pragma once
#include "TrackingWebApp.h"

// CApplicationTrackingDlg dialog
class CApplicationTrackingDlg : public CDialog
{
// Construction
public:
	CApplicationTrackingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_APPLICATIONTRACKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTrackingWebApp m_TrackingWeb;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
