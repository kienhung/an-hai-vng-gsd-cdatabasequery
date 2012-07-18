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
	if (m_hThread != NULL) {
		CloseHandle(m_hThread);
		::OutputDebugStringA("Close thread handle\n");
	}
	
	if (m_sConnectSocket != INVALID_SOCKET) {
		::OutputDebugStringA("ngat socket\n");
		shutdown(m_sConnectSocket, SD_BOTH);
		closesocket(m_sConnectSocket);
	}
}

void CConnectSocket:: SetThreadHandle(HANDLE hThread) {
	m_hThread = hThread;
}

BOOL CConnectSocket:: SendFolderName(const TCHAR strFolderName[]) {

	MESSAGE_HEADER messageHeader;
	ZeroMemory(&messageHeader, sizeof(MESSAGE_HEADER));

	messageHeader.iType = FILE_LIST_REQUEST;
	messageHeader.uiLength = lstrlen(strFolderName);

	if (SOCKET_ERROR == send(m_sConnectSocket, (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0)) {
		m_pdlgClient->DestroySocket(this);
		return FALSE;
	}

	if (SOCKET_ERROR == send(m_sConnectSocket, (char*)strFolderName, sizeof(TCHAR)*messageHeader.uiLength, 0)) {

	}

	return TRUE;
}

CClientDlg *CConnectSocket:: GetDlg() {
	return m_pdlgClient;
}