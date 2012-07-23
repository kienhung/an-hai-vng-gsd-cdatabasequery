#pragma once
#include "connectsocket.h"
#include "ClientDlg.h"
class CDownloadFileSocket :
	public CConnectSocket
{
protected:
	TCHAR *m_ptcSaveFolderPath;
	TCHAR *m_ptcFileName;
	__int64 m_iProgressDownload;
	int m_iIndexDownload;
	
public:
	CDownloadFileSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient, const TCHAR *ptcSaveFolderPath, const TCHAR *ptcFileName);
	virtual ~CDownloadFileSocket(void);
	void SetIndexDownload(int iIndex);
	virtual BOOL ReceiveFile(const TCHAR strFileName[]);
	virtual BOOL ReceiveFileData(unsigned __int64 ui64Size, HANDLE hFile);
	BOOL Request();
	BOOL Receive();
	//BOOL SendFileName(const TCHAR strFolderName[]);
};
