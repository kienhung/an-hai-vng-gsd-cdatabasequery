
// ClientDlg.h : header file
//

#pragma once
#include "resource.h"
#include "ListCtrlEx.h"
#include "MyCriticalSection.h"
#include <list>

using namespace std;
class CConnectSocket;
#define synchronized(M)  for(Lock M##_lock = M; M##_lock; M##_lock.setUnlock())
class CClientDlg : public CDialog
{
	
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	static DWORD WINAPI FolderDownloadingThreadFunction(LPVOID lpParam );
	static DWORD WINAPI FileDownloadingThreadFunction(LPVOID lpParam );
	void InsertItemDownload(int iIndex, LPCTSTR strFileName, unsigned __int64 iFileSize, int iStatus);
	int GetCountItemDownload();
	void UpdateStateItemDownload(const int *iIndex,const int *iPosition);
// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CEdit *m_edtFolderName;
	CEdit *m_edtPath;
	CListCtrlEx m_lstDownload;
	CMutex m_Mutex;
	CMyCriticalSection m_cs;
	UINT m_uiPort;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL GetIPAddressString(char *pcBuffer, size_t stMaxLength);
	
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnDownload();
	afx_msg void OnDestroy();
	SOCKET CreateConnectSocket();
	afx_msg void OnBnClickedBtnBrowse();
};
