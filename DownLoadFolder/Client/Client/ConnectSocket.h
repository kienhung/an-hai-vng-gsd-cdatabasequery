#pragma once

class CClientDlg;

class CConnectSocket
{
protected:
	SOCKET m_sConnectSocket;
	HANDLE m_hThread;
	CClientDlg *m_pdlgClient;
	__int64	m_llLastWriteModified;
public:
	
	CConnectSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient);
	CConnectSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient, const TCHAR *ptcSaveFolderPath, const TCHAR *pctFileName);

	void SetThreadHandle(HANDLE hThread);
	int Destroy();
	CClientDlg * GetDlg();
	virtual ~CConnectSocket(void);

	BOOL SendFileName(const TCHAR strFolderName[] ,int iType);
	virtual BOOL ReceiveFile(const TCHAR strFileName[]);
	void SetLastWriteModified(const __int64* lastModified);
protected:

	BOOL ReceiveFileSize(unsigned __int64 *pui64Size);
	virtual BOOL ReceiveFileData(unsigned __int64 ui64Size, HANDLE hFile);

};
