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
	BOOL m_bIsVisibleDlg;
	SYSTEMTIME m_stLastModifyBlackList;

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



	afx_msg void OnWindowPosChanging(WINDOWPOS *lpwndpos);
	DECLARE_EVENTSINK_MAP()
	void BeforeNavigate2ExplorerRegister(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);

protected:
	BOOL UpdateBlackList();
	BOOL PingServer();
	BOOL IsNeedDownloadBlackList(CString &strBlackListUrl);
	BOOL UpdateFileTime(LPCTSTR strFileURL, LPCTSTR strFilePath);
	BOOL UpdateFileTime(LPCTSTR strFilePath);
public:
	void NavigateComplete2ExplorerRegister(LPDISPATCH pDisp, VARIANT* URL);
	void WindowClosingExplorerRegister(BOOL IsChildWindow, BOOL* Cancel);
};
