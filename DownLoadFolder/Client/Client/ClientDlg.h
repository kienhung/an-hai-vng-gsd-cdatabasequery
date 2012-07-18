
// ClientDlg.h : header file
//

#pragma once
#include "resource.h"
#include <list>

using namespace std;
class CConnectSocket;

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	static DWORD WINAPI FolderDownloadingThreadFunction(LPVOID lpParam );

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CEdit *m_edtFolderName;

	UINT m_uiPort;
	CStringA m_ServerIpAddress;
	CString m_SavingPath;

	list<CConnectSocket*> m_lstConnectSockets;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDownload();
	void DestroySocket(CConnectSocket* pConnectSocket);
	afx_msg void OnDestroy();
};
