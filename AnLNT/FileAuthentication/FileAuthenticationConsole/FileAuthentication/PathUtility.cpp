#include "StdAfx.h"
#include "PathUtility.h"
#include <shlwapi.h>
#include <strsafe.h>

CPathUtility::CPathUtility(void)
{
}

CPathUtility::~CPathUtility(void)
{
}

CString CPathUtility::GetExeFilePath()
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

CString CPathUtility::GetParentPath( LPCTSTR strFileName )
{
	TCHAR strPath[MAX_PATH]={0};

	StringCchCopy(strPath, MAX_PATH, strFileName);

	if (FALSE == ::PathRemoveFileSpec(strPath)) {
		return L"";
	}
	return strPath;
}

BOOL CPathUtility::IsDirectory( LPCTSTR strFileName )
{
	DWORD dwFileAttributes = ::GetFileAttributes(strFileName);
	if (INVALID_FILE_ATTRIBUTES == dwFileAttributes ) {
		return FALSE;
	}

	if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}
	return FALSE;
}

CString CPathUtility::GetShortFileName( const CString &strLongFileName )
{
	int iIndex = strLongFileName.ReverseFind(L'\\');
	return strLongFileName.Right(strLongFileName.GetLength() - iIndex - 1);
}

BOOL CPathUtility::IsFileExist( LPCTSTR strFileName )
{

	WIN32_FIND_DATA FindFileData;

	HANDLE hFind = ::FindFirstFile(strFileName, &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	::FindClose(hFind);

	return TRUE;
}
