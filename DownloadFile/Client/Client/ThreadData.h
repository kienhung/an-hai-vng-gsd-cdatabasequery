#pragma once
#include "ListCtrlEx.h"
struct THREAD_DATA {
	SOCKET sConnectSocket;
	TCHAR strFileName[MAX_PATH];
	TCHAR strPath[MAX_PATH];
	int iIndex;
	CListCtrlEx* lstDownloadFile; 
};