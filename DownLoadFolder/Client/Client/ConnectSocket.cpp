#include "StdAfx.h"
#include "ConnectSocket.h"
#include "ClientDlg.h"
#include "Messages.h"

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

BOOL CConnectSocket:: SendFolderName(const TCHAR strFolderName[]) {

	if (lstrlen(strFolderName) + 1 > MAX_PATH) {
		return FALSE;
	}

	MESSAGE_HEADER messageHeader;
	ZeroMemory(&messageHeader, sizeof(MESSAGE_HEADER));

	messageHeader.iType = FILE_LIST_REQUEST;
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
	return TRUE;
}