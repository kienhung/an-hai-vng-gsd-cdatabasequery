
// ConnectToAccessDlg.h : header file
//

#pragma once
#include <afxcmn.h>
#include <afxdb.h>

// CConnectToAccessDlg dialog
class CConnectToAccessDlg : public CDialog
{
// Construction
public:
	CConnectToAccessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONNECTTOACCESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	BOOL ConnectToDatabase(const TCHAR* strPath);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
};
