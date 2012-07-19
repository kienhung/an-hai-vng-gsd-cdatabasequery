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
	int Destroy();
	CClientDlg * GetDlg();
	~CConnectSocket(void);

	BOOL SendFolderName(const TCHAR strFolderName[]);
	BOOL ReceiveFile(const TCHAR strFileName[]);

protected:

	BOOL ReceiveFileSize(unsigned __int64 *pui64Size);
	BOOL ReceiveFileData(unsigned __int64 ui64Size, HANDLE hFile);

};
