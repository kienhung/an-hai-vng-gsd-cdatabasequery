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


protected:
	HICON m_hIcon;
	UINT m_uiPort;

	SOCKET m_sListener;

	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam );

	BOOL ProcessSocketMessage(WPARAM wParam, LPARAM lParam);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	BOOL InitListener();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
};
