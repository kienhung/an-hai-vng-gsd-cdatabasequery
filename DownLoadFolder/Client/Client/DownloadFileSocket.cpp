#include "StdAfx.h"
#include "DownloadFileSocket.h"
#include <Strsafe.h>

CDownloadFileSocket::CDownloadFileSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient, const TCHAR *ptcSaveFolderPath, const TCHAR *ptcFileName)
:CConnectSocket(sConnectSocket, pdlgClient)
{
	int uiLength = lstrlen(ptcFileName) + 1;
	m_ptcFileName = new TCHAR[uiLength];
	StringCchCopy(m_ptcFileName, uiLength, ptcFileName);

	uiLength = lstrlen(ptcSaveFolderPath) + 1;
	m_ptcSaveFolderPath = new TCHAR[uiLength];
	StringCchCopy(m_ptcSaveFolderPath, uiLength, ptcSaveFolderPath);
}

CDownloadFileSocket::~CDownloadFileSocket(void)
{
	if (m_ptcFileName != NULL) {
		delete[] m_ptcFileName;
	}

	if (m_ptcSaveFolderPath != NULL) {
		delete[] m_ptcSaveFolderPath;
	}
}

BOOL CDownloadFileSocket::SendFileName( const TCHAR strFolderName[] )
{

	return TRUE;
}
