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
	const TCHAR* RecevieFolderName(size_t uiLength);

	CServerDlg * GetDlg();
	BOOL GetMessageHeader(int *piMessageType, size_t *puiMessageLength = NULL);

	~CConnectSocket(void);
};
