// ClientDlg.h : header file
//

#pragma once
#include "ListCtrlEx.h"

// CClientDlg dialog
class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CListCtrlEx m_LstDownload;

	HICON m_hIcon;
	UINT m_uiServerPort;

	BOOL GetIPAddressString(char *pcBuffer, size_t stMaxLength);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
};
