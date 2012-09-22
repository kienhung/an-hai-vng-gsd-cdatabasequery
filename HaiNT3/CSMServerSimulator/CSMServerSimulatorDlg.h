// CSMServerSimulatorDlg.h : header file
//

#pragma once

// CCSMServerSimulatorDlg dialog
class CCSMServerSimulatorDlg : public CDialog
{
// Construction
public:
	CCSMServerSimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSMSERVERSIMULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	VOID InitListCtrWebHistory();
	VOID InsertItemHistory(const CString& strURL, const CString& strTime = _T(""));
// Implementation
protected:
	HICON m_hIcon;
	CListCtrl	m_lstWebHistory;

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnAsyncSocketNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
