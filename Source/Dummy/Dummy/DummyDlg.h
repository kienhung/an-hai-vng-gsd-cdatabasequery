// DummyDlg.h : header file
//

#pragma once
#include "WebBrowser2.h"

#define WM_TRAY_ICON_NOTIFY			(WM_USER + 1)
#define WM_CHECK_SHOW_REGISTER_INFO	(WM_USER + 2)

// CDummyDlg dialog
class CDummyDlg : public CDialog
{
private:
	BOOL m_bIsRegistered;

	void AddIconToSystemTray();
	void RemoveIconFromSystemTray();
	void ShowRegisterInfo();

// Construction
public:
	CDummyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DUMMY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	CWebBrowser2 m_webRegister;
	afx_msg LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnExit();
	afx_msg void OnRegisterInfo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};