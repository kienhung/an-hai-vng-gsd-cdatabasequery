#include "stdafx.h"
#include "ThreadFunction.h"
#include "Messages.h"
#include "MessageHandler.h"
#include "Threaddata.h"


bool SendDownloadFileMessage(SOCKET sConnectSocket, const TCHAR strFileName[], int *piLastError){

	MESSAGE_HEADER messageHeader;
	messageHeader.iType = DOWNLOAD_FILE;
	messageHeader.iLength = 0;

	if (send(sConnectSocket,  (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0) == SOCKET_ERROR) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	FILE_NAME_MESSAGE fileNameMessage;
	_tcscpy_s(fileNameMessage.strFileName, MAX_PATH, strFileName);

	if (send(sConnectSocket, (char*)&fileNameMessage, sizeof(FILE_NAME_MESSAGE), 0) == SOCKET_ERROR) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}
	return true;
}

bool ReceiveFileSize(SOCKET sConnectSocket, unsigned __int64 *pi64FizeSize, int *piLastError) {
	
	int bytesReceived = recv(sConnectSocket, (char*)pi64FizeSize, sizeof(unsigned __int64), 0);

	if(sizeof(unsigned __int64) != bytesReceived) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}
	return true;
}

bool WriteData(SOCKET sConnectSocket, const TCHAR strFileName[], const unsigned __int64 &i64FizeSize, int *piLastError) {
	


	unsigned __int64 i64Count = 0;

	HANDLE hFile = ::CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (INVALID_HANDLE_VALUE == hFile) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	const int BUFFER_LENGTH = 2048;
	char strBuffer[BUFFER_LENGTH] = {0};
	int bytesReceived = 0;
	DWORD dwBytesWritten = 0;

	while (i64Count < i64FizeSize) {

		bytesReceived = recv(sConnectSocket, strBuffer, BUFFER_LENGTH, 0);

		if (bytesReceived < 0) {
			*piLastError = HandleError(sConnectSocket);
			CloseHandle(hFile);
			return false;
		}

		::WriteFile(hFile, strBuffer, bytesReceived, &dwBytesWritten, NULL);
		i64Count += bytesReceived;
	}
	CloseHandle(hFile);
	return true;
}

bool WriteData(SOCKET sConnectSocket, const TCHAR strFileName[], const unsigned __int64 &i64FizeSize, CListCtrlEx* plstDownloadFile, int iIndex, int *piLastError) {
	plstDownloadFile->InsertItemDownload(iIndex, strFileName, i64FizeSize, 10);
	unsigned __int64 i64Count = 0;

	HANDLE hFile = ::CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (INVALID_HANDLE_VALUE == hFile) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	const int BUFFER_LENGTH = 2048;
	char strBuffer[BUFFER_LENGTH] = {0};
	int bytesReceived = 0;
	DWORD dwBytesWritten = 0;

	while (i64Count < i64FizeSize) {

		bytesReceived = recv(sConnectSocket, strBuffer, BUFFER_LENGTH, 0);

		if (bytesReceived < 0) {
			*piLastError = HandleError(sConnectSocket);
			CloseHandle(hFile);
			return false;
		}

		::WriteFile(hFile, strBuffer, bytesReceived, &dwBytesWritten, NULL);
		i64Count += bytesReceived;
		int iStatus = int((i64Count *100) / i64FizeSize);
		//plstDownloadFile->UpdateStatusDownload(iIndex, iStatus);
	}
	CloseHandle(hFile);
	return true;
}

bool CheckFileExist(SOCKET sConnectSocket, int *piLastError) {

	MESSAGE_HEADER messageHeader;
	ZeroMemory(&messageHeader, sizeof(MESSAGE_HEADER));
	int bytesReceived = recv(sConnectSocket,(char*)&messageHeader, sizeof(MESSAGE_HEADER), 0);

	if (sizeof(MESSAGE_HEADER) != bytesReceived ) {
		*piLastError = HandleError(sConnectSocket);
		return false;
	}

	if (FILE_NOT_FOUND == messageHeader.iType) {

		HandleError(sConnectSocket);
		*piLastError = 0;
		return false;

	} else if (FILE_FOUND == messageHeader.iType) {
		return true;
	}

	return true;
}


CString CreateFullPath(const TCHAR strLongFileName[], const TCHAR strPath[]) {
	CString cstrShortFileName = strLongFileName;
	int iFoundIndex = cstrShortFileName.ReverseFind(L'\\');
	if (iFoundIndex >= 0) {
		cstrShortFileName = cstrShortFileName.Right(cstrShortFileName.GetLength() - iFoundIndex - 1);
	}
	CString cstrPath;
	cstrPath.Format(_T("%s\\%s"), strPath, cstrShortFileName.GetBuffer());
	return cstrPath;
}


DWORD WINAPI SocketCommunicationThreadFunction(LPVOID lpParam ) {

	THREAD_DATA *pThreadData = (THREAD_DATA *)lpParam ;

	TCHAR strFileName[MAX_PATH];
	TCHAR strPath[MAX_PATH];

	_tcscpy_s(strFileName, MAX_PATH, pThreadData->strFileName);
	_tcscpy_s(strPath, MAX_PATH, pThreadData->strPath);
	int iIndex = pThreadData->iIndex;
	CListCtrlEx* plstDownloadFile = pThreadData->lstDownloadFile; 
	SOCKET sConnectSocket = pThreadData->sConnectSocket;

	delete pThreadData;

	int iLastError;
	if (SendDownloadFileMessage(sConnectSocket, strFileName, &iLastError) == false) {
		return iLastError;
	}

	if (CheckFileExist(sConnectSocket, &iLastError) == false) {
			::OutputDebugString(_T("khong ton tai file muon down\n"));
	} else {

		unsigned __int64 i64FizeSize;

		if (ReceiveFileSize(sConnectSocket, &i64FizeSize, &iLastError) == false) {
			return iLastError;
		}

		CString cstrPath = CreateFullPath(strFileName, strPath);

		
		if (WriteData(sConnectSocket, cstrPath.GetBuffer(), i64FizeSize, plstDownloadFile, iIndex, &iLastError) == false) {
			return iLastError;
		}
		/*
		if (WriteData(sConnectSocket, cstrPath.GetBuffer(), i64FizeSize, &iLastError) == false) {
			return iLastError;
		}
		*/
		shutdown(sConnectSocket, SD_BOTH);
		closesocket(sConnectSocket);
	}
	return 0;
}
