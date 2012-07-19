#include "StdAfx.h"
#include "FileServices.h"
#include <strsafe.h>
CFileServices::CFileServices(void)
{
}

CFileServices::~CFileServices(void)
{
}

unsigned __int64 CFileServices::GetFileSize(HANDLE hFile) {

	if (INVALID_HANDLE_VALUE != hFile) {

		LARGE_INTEGER bigIntFileSize;
		if (FALSE == ::GetFileSizeEx(hFile, &bigIntFileSize)) {
			return 0;
		}
		return bigIntFileSize.QuadPart;
	}
	return 0;
}

BOOL CFileServices:: CreateFullPath(TCHAR strFullPath[], size_t uiMaxLength, const TCHAR strRoot[], const TCHAR strName[]) {
	
	HRESULT hResult = StringCchPrintf(strFullPath, uiMaxLength, _T("%s\\%s"), strRoot,  strName);
	
	if (hResult == S_OK) {
		return TRUE;
	}	

	return FALSE;
}

BOOL CFileServices:: CreateFilesListFilePath(TCHAR strFilesListFilePath[],  size_t uiMaxLength, const TCHAR strRoot[]) {

	SYSTEMTIME serverTime;
	GetLocalTime(&serverTime);
	HRESULT hResult = StringCchPrintf(strFilesListFilePath, uiMaxLength, _T("%s\\%d-%d-%d-%d-%d-%d-%d.ini"), strRoot,  serverTime.wDay, serverTime.wMonth, serverTime.wYear, serverTime.wHour, serverTime.wMinute, serverTime.wSecond, serverTime.wMilliseconds);
	
	if (hResult == S_OK) {
		return TRUE;
	}	
	return FALSE;
}

BOOL CFileServices::IsDirectory(const TCHAR strPath[]) {

	DWORD dwFileAttributes = ::GetFileAttributes(strPath);
	if (INVALID_FILE_ATTRIBUTES == dwFileAttributes ) {
		return FALSE;
	}

	if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}
	return FALSE;

}