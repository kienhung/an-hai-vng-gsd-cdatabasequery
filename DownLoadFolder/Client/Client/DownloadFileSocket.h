#pragma once
#include "connectsocket.h"

class CDownloadFileSocket :
	public CConnectSocket
{
protected:
	TCHAR *m_ptcSaveFolderPath;
	TCHAR *m_ptcFileName;
public:
	CDownloadFileSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient, const TCHAR *ptcSaveFolderPath, const TCHAR *ptcFileName);
	virtual ~CDownloadFileSocket(void);

	BOOL SendFileName(const TCHAR strFolderName[]);
};
