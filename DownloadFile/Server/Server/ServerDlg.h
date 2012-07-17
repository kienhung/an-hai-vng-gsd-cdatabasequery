// ServerDlg.h : header file
//

#pragma once


// CServerDlg dialog
class CServerDlg : public CDialog
{
// Construction
public:
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CEdit m_edtPath;
protected:
	HICON m_hIcon;
	UINT m_uiPort;

	SOCKET m_sListener;

	virtual BOOL OnInitDialog();



	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	BOOL InitListener();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnOk();
};
