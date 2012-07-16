#include "StdAfx.h"
#include "MessageHandler.h"
#include "Messages.h"

bool HandleDownloadFileMessage(SOCKET sConnectSocket, int iLength, int *piLastError) {


	::OutputDebugString(_T("Cho Nhan Duong Dan Den File\n"));
	*piLastError = 0;

	FILE_NAME_MESSAGE fileNameMessage;
	int bytesReceived = recv(sConnectSocket, (char*)&fileNameMessage, sizeof(FILE_NAME_MESSAGE), 0);

	if (sizeof(FILE_NAME_MESSAGE) != bytesReceived) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	TCHAR strPath[MAX_PATH];
	_stprintf_s(strPath, MAX_PATH, _T("D:\\Public\\%s"), fileNameMessage.strFileName);

	::OutputDebugString(strPath);
	::OutputDebugString(_T("\n"));


	return true;
}

int HandleError(SOCKET socket) {

	int iError = WSAGetLastError();

	shutdown(socket, SD_BOTH);
	closesocket(socket);

	return iError;
}