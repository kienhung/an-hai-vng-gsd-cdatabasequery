#include "StdAfx.h"
#include "FileServices.h"
#include <strsafe.h>
CFileServices::CFileServices(void)
{
	m_ptcParentPath = NULL;
}

CFileServices::~CFileServices(void)
{
	if (m_ptcParentPath != NULL) {
		delete []m_ptcParentPath;
	}
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

const TCHAR * CFileServices::GetParentPath( const TCHAR strPath[] )
{

	int iLength = lstrlen(strPath);
	int iIndex;

	for (iIndex = iLength - 1; iIndex >= 0; iIndex--) {
		if (strPath[iIndex] == L'\\') {
			break;
		}
	}

	if (iIndex < 0) {
		return NULL;
	}

	if (NULL != m_ptcParentPath) {
		delete[] m_ptcParentPath;
	}

	m_ptcParentPath = new TCHAR[iIndex + 1];

	if (NULL == m_ptcParentPath) {
		return NULL;
	}
	StringCchCopyN(m_ptcParentPath, iIndex + 1, strPath, iIndex);
	return m_ptcParentPath;
}

BOOL CFileServices::CustomCreateDirectory(const TCHAR *strPath)
{
	if (IsDirectory(strPath) == TRUE) {
		return TRUE;
	}

	if (::CreateDirectory(strPath, NULL) == TRUE) {
		return TRUE;
	}

	CFileServices fileServices;
	CONST TCHAR * ptcParentPath = fileServices.GetParentPath(strPath);

	if (NULL == ptcParentPath) {
		return FALSE;
	}

	if (CustomCreateDirectory(ptcParentPath) == TRUE) {
		::CreateDirectory(strPath, NULL);
		return TRUE;
	}
	return FALSE;
}
