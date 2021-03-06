#include "StdAfx.h"
#include "MessageHandler.h"
#include "Messages.h"

bool HandleDownloadFileMessage(SOCKET sConnectSocket, const TCHAR strRootFolder[], int *piLastError) {

	*piLastError = 0;

	TCHAR strPath[MAX_PATH];
	if (ReceiveFileName(sConnectSocket, strPath, MAX_PATH, strRootFolder, piLastError) == false) {
		return false;
	}

	HANDLE hFile = ::CreateFile(strPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (INVALID_HANDLE_VALUE == hFile) {
		SendFileNotFoundMessage(sConnectSocket, piLastError);
		return false;
	}
	
	if(SendFileFoundMessage(sConnectSocket, piLastError) == false) {
		CloseHandle(hFile);
		return false;
	}

	if (SendFileSize(sConnectSocket, hFile, piLastError) == false) {
		CloseHandle(hFile);
		return false;
	}
	

	const int BUFFER_LENGTH = 2048;
	char strBuffer[BUFFER_LENGTH] = {0};
	DWORD  dwBytesRead = 0;

	do {
		::ReadFile(hFile, strBuffer, BUFFER_LENGTH, &dwBytesRead, NULL);
		if (dwBytesRead > 0) {
			if (send(sConnectSocket, strBuffer, dwBytesRead , 0) == SOCKET_ERROR) {
				*piLastError = HandleError(sConnectSocket);
				CloseHandle(hFile);
				return false;
			}
		}
	} while (dwBytesRead != 0);
	CloseHandle(hFile);

	return true;
}

bool ReceiveFileName(SOCKET sConnectSocket, TCHAR strFileName[], int iMaxLength, const TCHAR strRootFolder[], int *piLastError) {
	
	FILE_NAME_MESSAGE fileNameMessage;
	int bytesReceived = recv(sConnectSocket, (char*)&fileNameMessage, sizeof(FILE_NAME_MESSAGE), 0);

	if (sizeof(FILE_NAME_MESSAGE) != bytesReceived) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}
	
	_stprintf_s(strFileName, iMaxLength, _T("%s\\%s"), strRootFolder, fileNameMessage.strFileName);
	return true;
}

bool SendFileFoundMessage(SOCKET sConnectSocket, int *piLastError) {

	MESSAGE_HEADER messageHeader;
	messageHeader.iLength = 0;
	messageHeader.iType = FILE_FOUND;

	if (send(sConnectSocket,  (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0) == SOCKET_ERROR) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	return true;
}


void SendFileNotFoundMessage(SOCKET sConnectSocket, int *piLastError) {

	MESSAGE_HEADER messageHeader;
	messageHeader.iLength = 0;
	messageHeader.iType = FILE_NOT_FOUND;

	send(sConnectSocket,  (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0);
	*piLastError = HandleError(sConnectSocket);
}

bool SendFileSize(SOCKET sConnectSocket, HANDLE hFile, int *piLastError) {

	LARGE_INTEGER largeIntegerSize;

	if (INVALID_FILE_SIZE == ::GetFileSizeEx(hFile, &largeIntegerSize)) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	unsigned __int64 i64FizeSize = largeIntegerSize.QuadPart;
	if (send(sConnectSocket, (char*)&i64FizeSize, sizeof(i64FizeSize), 0) == SOCKET_ERROR) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}
	return true;


}

int HandleError(SOCKET socket) {

	int iError = WSAGetLastError();

	shutdown(socket, SD_BOTH);
	closesocket(socket);

	return iError;
}
