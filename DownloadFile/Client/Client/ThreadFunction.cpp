#include "stdafx.h"
#include "ThreadFunction.h"
#include "Messages.h"
#include "MessageHandler.h"

DWORD WINAPI SocketCommunicationThreadFunction(LPVOID lpParam ) {

	SOCKET *pSocket = (SOCKET*)lpParam ;
	SOCKET sConnectSocket = *pSocket;
	delete pSocket;

	//const int BUFFER_LENGTH = 512;
	//char strBuffer[BUFFER_LENGTH] = {0};
	
	MESSAGE_HEADER messageHeader;
	messageHeader.iType = DOWNLOAD_FILE;
	messageHeader.iLength = 0;

	if (send(sConnectSocket,  (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0) == SOCKET_ERROR) {
		return HandleError(sConnectSocket);
	}

	FILE_NAME_MESSAGE fileNameMessage;
	_tcscpy_s(fileNameMessage.strFileName, MAX_PATH, _T("xxx.txt"));

	if (send(sConnectSocket, (char*)&fileNameMessage, sizeof(FILE_NAME_MESSAGE), 0) == SOCKET_ERROR) {
		return HandleError(sConnectSocket);
	}

	::OutputDebugString(_T("cho phan hoi cho biet co tim thay file hay khong\n"));
	ZeroMemory(&messageHeader, sizeof(MESSAGE_HEADER));
	int bytesReceived = recv(sConnectSocket,(char*)&messageHeader, sizeof(MESSAGE_HEADER), 0);

	if (sizeof(MESSAGE_HEADER) != bytesReceived ) {
		return HandleError(sConnectSocket);
	}

	if (FILE_NOT_FOUND == messageHeader.iType) {
		::OutputDebugString(_T("khong tim thay file\n"));
	} else if (FILE_FOUND == messageHeader.iType) {
		::OutputDebugString(_T("tim thay file\n"));
	}

	shutdown(sConnectSocket, SD_BOTH);
	closesocket(sConnectSocket);
	return 0;
}