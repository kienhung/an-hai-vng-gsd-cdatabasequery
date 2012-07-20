#include "StdAfx.h"
#include "DownloadFileSocket.h"
#include <Strsafe.h>
#include "Messages.h"
#include "FileServices.h"

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

BOOL CDownloadFileSocket::Request() {

	if (FALSE == SendFileName(m_ptcFileName, DOWNLOAD_FILE)) {
		::OutputDebugStringA("Send file name thanh cong\n");
	} 
	::OutputDebugStringA("Send file name thanh cong\n");
	return TRUE;
}

BOOL CDownloadFileSocket::Receive() {

	TCHAR strFilePath[MAX_PATH];
	CFileServices fileServices;

	fileServices.CreateFullPath(strFilePath, MAX_PATH, m_ptcSaveFolderPath, m_ptcFileName);
	::OutputDebugStringA("Duong dan luu file la: ");
	::OutputDebugString(strFilePath);
	::OutputDebugStringA("\n");
	if (FALSE == ReceiveFile(strFilePath)) {
		return FALSE;
	}

	return TRUE;
}
