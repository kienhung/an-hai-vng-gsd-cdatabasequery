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

	TCHAR *m_ptcFileName;

public:
	CConnectSocket(SOCKET sConnectSocket, CServerDlg *pdlgServer);
	void SetThreadHandle(HANDLE hThread);
	CServerDlg * GetDlg();
	int Destroy();

	const TCHAR* RecevieFileName(int uiLength);
	BOOL GetMessageHeader(int *piMessageType, int *puiMessageLength = NULL);
	BOOL SendFile(HANDLE hFile);
	BOOL SendFileSize(unsigned __int64 *pui64Size);
	~CConnectSocket(void);
protected:

	BOOL SendFileData(unsigned __int64 ui64FileSize, HANDLE hFile);
};
