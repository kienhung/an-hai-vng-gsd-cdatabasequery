
// ServerDlg.h : header file
//

#pragma once
#include "resource.h"

#include <list>
using namespace std;

class CConnectSocket;

class CServerDlg : public CDialog
{

public:
	static DWORD WINAPI SocketListeningThreadFunction(LPVOID lpParam );
	static DWORD WINAPI FolderDownloadingThreadFunction(LPVOID lpParam );

	CServerDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_SERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	UINT m_uiPort;

	SOCKET m_sListener;
	HANDLE m_hListenThread;

	CString m_strRootFolder;

	BOOL InitListener();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	int ProcessFileListRequest(CConnectSocket* pConnectSocket, int uiLength);
	void DestroySocket(CConnectSocket* pConnectSocket);
};
