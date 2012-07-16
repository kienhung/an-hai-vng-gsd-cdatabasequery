#pragma once


bool HandleDownloadFileMessage(SOCKET sConnectSocket, int *piLastError);

bool HandleDownloadFileMessage(SOCKET sConnectSocket, const TCHAR strRootFolder[], int *piLastError);
bool ReceiveFileName(SOCKET sConnectSocket, TCHAR strFileName[], int iMaxLength, const TCHAR strRootFolder[], int *piLastError);
void SendFileNotFoundMessage(SOCKET sConnectSocket, int *piLastError);
bool SendFileFoundMessage(SOCKET sConnectSocket, int *piLastError);
bool SendFileSize(SOCKET sConnectSocket, HANDLE hFile, int *piLastError);

int HandleError(SOCKET socket);
