#include "StdAfx.h"
#include "PathUtility.h"
#include <shlwapi.h>

CPathUtility::CPathUtility(void)
{
}

CPathUtility::~CPathUtility(void)
{
}

CString CPathUtility::GetExeDirectory()
{
	TCHAR strModulePath[MAX_PATH]={0};

	if (0 == ::GetModuleFileName(NULL, strModulePath, MAX_PATH)) {
		return L"";
	}

	if (FALSE == ::PathRemoveFileSpec(strModulePath)) {
		return L"";
	}

	return strModulePath;
}

BOOL CPathUtility::IsPathDirectory( LPCTSTR strPath )
{
	DWORD dwFileAttributes = ::GetFileAttributes(strPath);
	if (INVALID_FILE_ATTRIBUTES == dwFileAttributes ) {
		return FALSE;
	}

	if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}
	return FALSE;
}
