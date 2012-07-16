#pragma once


bool HandleDownloadFileMessage(SOCKET sConnectSocket, int iLength, int *piLastError);
int HandleError(SOCKET socket);
