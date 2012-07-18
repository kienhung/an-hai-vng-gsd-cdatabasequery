#include "StdAfx.h"
#include "DuyetFile.h"

CDuyetFile::CDuyetFile(void)
{
}

CDuyetFile::~CDuyetFile(void)
{
}

void CDuyetFile::ApproveFolder(const TCHAR *strPath)
{
	

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(strPath, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("Đường dẫn không hợp lệ"));
		return;
	}

	while(FindNextFile(hFind, &FindFileData) != 0)
	{
		INFOFILE infoFile;
		
		TCHAR strFilePath[MAX_PATH];
		_tcscpy_s(strFilePath, strPath);
		int length = wcslen(strFilePath);
		strFilePath[length -1] = L'\0';
		_tcscat_s(strFilePath, FindFileData.cFileName);
		
		TCHAR bufferHigh[32];
		TCHAR bufferLow[32];
		wsprintf(bufferHigh, _T("%d"), FindFileData.ftLastWriteTime.dwHighDateTime);
		wsprintf(bufferLow, _T("%d"), FindFileData.ftLastWriteTime.dwLowDateTime);
		wcscat_s(bufferHigh, bufferLow);

		//infoFile.ulSize = GetFileSize(hFind, &FindFileData.nFileSizeHigh);
		infoFile.cTypeFile = 0;
		wcscpy_s(infoFile.strFileName, strFilePath);
		infoFile.ullLastModified = _wtoi64(bufferHigh);
		
		lstFile.push_back(infoFile);
		if(GetFileAttributes(strFilePath) == FILE_ATTRIBUTE_DIRECTORY)
		{
			infoFile.cTypeFile = 1;
			ApproveFolder(strFilePath);
		}
		
	}

	FindClose(hFind);
}