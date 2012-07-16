#pragma once
#include "ListCtrlEx.h"

DWORD WINAPI SocketCommunicationThreadFunction(LPVOID lpParam );
bool SendDownloadFileMessage(SOCKET sConnectSocket, const TCHAR strFileName[], int *piLastError);
bool ReceiveFileSize(SOCKET sConnectSocket, unsigned __int64 *pi64FizeSize, int *piLastError);
bool CheckFileExist(SOCKET sConnectSocket, int *piLastError);

bool WriteData(SOCKET sConnectSocket, const TCHAR strFileName[], const unsigned __int64 &i64FizeSize, int *piLastError);
bool WriteData(SOCKET sConnectSocket, const TCHAR strFileName[], const unsigned __int64 &i64FizeSize, CListCtrlEx* plstDownloadFile, int iIndex, int *piLastError);
CString CreateFullPath(const TCHAR strLongFileName[], const TCHAR strPath[]);