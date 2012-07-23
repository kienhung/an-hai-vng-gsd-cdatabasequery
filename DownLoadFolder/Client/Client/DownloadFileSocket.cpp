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
	m_iProgressDownload = 0;
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
void CDownloadFileSocket::SetIndexDownload(int iIndex)
{
	m_iIndexDownload = iIndex;
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
BOOL CDownloadFileSocket::ReceiveFile(const TCHAR strFileName[])
{
	unsigned __int64 ui64Size = 0;

	if (FALSE == ReceiveFileSize(&ui64Size)) {
		return FALSE;
	}
	
	if (0 == ui64Size) {
		AfxMessageBox(_T("File not found"), MB_ICONSTOP);
		return FALSE;
	}

	HANDLE hFile = ::CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (INVALID_HANDLE_VALUE == hFile) {
		return FALSE;
	}
	
	BOOL bResult = ReceiveFileData(ui64Size, hFile);
	CloseHandle(hFile);

	return bResult;
}
BOOL CDownloadFileSocket::ReceiveFileData(unsigned __int64 ui64Size, HANDLE hFile)
{
	::OutputDebugStringA("Client: Nhay vao ham receiveFileData\n");

	const int BUFFER_LENGTH = 4096;
	char strBuffer[BUFFER_LENGTH] = {0};

	int bytesReceived = 0;
	DWORD dwBytesWritten = 0;
	
	unsigned __int64 ui64Count = 0;
	
	while (ui64Count < ui64Size) {

		bytesReceived = recv(m_sConnectSocket, strBuffer, BUFFER_LENGTH, 0);
	
		if (SOCKET_ERROR  == bytesReceived) {
			return FALSE;
		}

		if (FALSE == ::WriteFile(hFile, strBuffer, bytesReceived, &dwBytesWritten, NULL)) {
			return FALSE;
		}

		ui64Count += bytesReceived;
		//int iPerDownload = (int)(((__int64)ui64Count*100) / ui64Size);
		m_pdlgClient->UpdateStateItemDownload(&m_iIndexDownload, &bytesReceived);
	}
	
	
	_LARGE_INTEGER lInt;
	lInt.QuadPart = m_llLastWriteModified;
	FILETIME fileTime;
	fileTime.dwHighDateTime = lInt.HighPart;
	fileTime.dwLowDateTime = lInt.LowPart;
	SetFileTime(hFile, NULL, NULL, &fileTime);
	return TRUE;
}