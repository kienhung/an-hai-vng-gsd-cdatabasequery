// ClientDlg.h : header file
//

#pragma once
#include "ListCtrlEx.h"


// CClientDlg dialog
class CClientDlg : public CDialog
{
private:
	static DWORD WINAPI SocketCommunicationThreadFunction1(LPVOID lpParam );
	void ProcessThreadFunc();
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	CString m_strServerFileName;
	CString m_strClientFileName;
	CString m_strSavePath;

// Implementation
protected:
	CListCtrlEx m_LstDownload;

	HICON m_hIcon;
	UINT m_uiServerPort;

	BOOL GetIPAddressString(char *pcBuffer, size_t stMaxLength);
	void DownloadFile();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedBtn();
};
