#include "StdAfx.h"
#include "FileUtility.h"

CFileUtility::CFileUtility(void)
{
}

CFileUtility::~CFileUtility(void)
{
}

BOOL CFileUtility::GetFileSize( LPCTSTR strFileName, unsigned __int64 *pui64FileSize )
{

	HANDLE hFile = ::CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		return FALSE;
	}

	BOOL bResult =  GetFileSize(hFile, pui64FileSize);

	::CloseHandle(hFile);

	return bResult;
}

BOOL CFileUtility::GetFileSize( HANDLE hFile, unsigned __int64 *pui64FileSize )
{
	if (INVALID_HANDLE_VALUE == hFile) {
		return FALSE;
	}

	LARGE_INTEGER bigIntFileSize;

	if (FALSE == ::GetFileSizeEx(hFile, &bigIntFileSize)) {
		return FALSE;
	}

	*pui64FileSize = bigIntFileSize.QuadPart;
	return TRUE;
}
