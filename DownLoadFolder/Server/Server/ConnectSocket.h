#pragma once
//#include "ServerDlg.h"
#include "Messages.h"

class CServerDlg;

class CConnectSocket
{
protected:
	SOCKET m_sConnectSocket;
	CServerDlg *m_dlgServer;
	HANDLE m_hThread;

	TCHAR *m_ptcFolderName;

public:
	CConnectSocket(SOCKET sConnectSocket, CServerDlg *pdlgServer);
	void SetThreadHandle(HANDLE hThread);
	CServerDlg * GetDlg();
	int Destroy();

	const TCHAR* RecevieFolderName(int uiLength);
	BOOL GetMessageHeader(int *piMessageType, int *puiMessageLength = NULL);
	BOOL SendFile(HANDLE hFile);
	~CConnectSocket(void);
protected:
	BOOL SendFileSize(unsigned __int64 *pui64Size);
	BOOL SendFileData(unsigned __int64 ui64FileSize, HANDLE hFile);
};
