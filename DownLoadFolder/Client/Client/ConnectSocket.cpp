#include "StdAfx.h"
#include "ConnectSocket.h"
#include "ClientDlg.h"
#include "Messages.h"
#include <windows.h>
CConnectSocket::CConnectSocket(SOCKET sConnectSocket, CClientDlg *pdlgClient)
{
	m_sConnectSocket = sConnectSocket;
	m_pdlgClient = pdlgClient;
	m_hThread = NULL;
}

CConnectSocket::~CConnectSocket(void)
{

}

void CConnectSocket:: SetThreadHandle(HANDLE hThread) {
	m_hThread = hThread;
}

BOOL CConnectSocket:: SendFileName(const TCHAR strFolderName[] ,int iType) {

	if (lstrlen(strFolderName) + 1 > MAX_PATH) {
		return FALSE;
	}

	MESSAGE_HEADER messageHeader;
	ZeroMemory(&messageHeader, sizeof(MESSAGE_HEADER));

	messageHeader.iType = iType;
	messageHeader.uiLength = lstrlen(strFolderName);

	if (SOCKET_ERROR == send(m_sConnectSocket, (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0)) {
		return FALSE;
	}

	if (SOCKET_ERROR == send(m_sConnectSocket, (char*)strFolderName, sizeof(TCHAR)*messageHeader.uiLength, 0)) {
		return FALSE;
	}
	return TRUE;
}

CClientDlg *CConnectSocket:: GetDlg() {
	return m_pdlgClient;
}


int CConnectSocket::Destroy()
{
	if (m_hThread != NULL) {
		CloseHandle(m_hThread);
	}

	if (m_sConnectSocket != INVALID_SOCKET) {
		shutdown(m_sConnectSocket, SD_BOTH);
		closesocket(m_sConnectSocket);
	}
	delete this;

	return GetLastError();
}

BOOL CConnectSocket::ReceiveFile(const TCHAR strFileName[]) {

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

BOOL CConnectSocket::ReceiveFileSize(unsigned __int64 *pui64Size) {

	::OutputDebugStringA("Client: Cho nhat file size\n");
	int bytesReceived = recv(m_sConnectSocket, (char*)pui64Size, sizeof(unsigned __int64), 0);

	if (bytesReceived != sizeof(unsigned __int64)) {
		return FALSE;
	}
	return TRUE;
}

BOOL CConnectSocket::ReceiveFileData(unsigned __int64 ui64Size, HANDLE hFile) {
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
	}
	
	
	_LARGE_INTEGER lInt;
	lInt.QuadPart = m_llLastWriteModified;
	FILETIME fileTime;
	fileTime.dwHighDateTime = lInt.HighPart;
	fileTime.dwLowDateTime = lInt.LowPart;
	SetFileTime(hFile, NULL, NULL, &fileTime);
	return TRUE;
}

void CConnectSocket::SetLastWriteModified(const __int64* lastModified)
{
	m_llLastWriteModified = *lastModified;
}