#pragma once

class CClientDlg;

class CConnectSocket
{
protected:
	SOCKET m_sConnectSocket;
	HANDLE m_hThread;
	CClientDlg *m_pdlgClient;
public:

	CConnectSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient);
	void SetThreadHandle(HANDLE hThread);

	BOOL SendFolderName(const TCHAR strFolderName[]);
	int Destroy();
	CClientDlg * GetDlg();

	~CConnectSocket(void);
};
