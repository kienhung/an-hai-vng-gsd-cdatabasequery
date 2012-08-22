#include "StdAfx.h"
#include "MyPath.h"
#include <shlwapi.h>
#include <strsafe.h>

CMyPath::CMyPath(void)
{
}

CMyPath::~CMyPath(void)
{
}

CString CMyPath::TransferSourcePath( LPCTSTR strSource, LPCTSTR strDest, LPCTSTR strFileName )
{
	CString strPath = strFileName;
	strPath.Delete(0, lstrlen(strSource));
	strPath.Insert(0, strDest);

	return strPath;
}

CString CMyPath::GetExeFilePath()
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

CString CMyPath::GetParentPath( LPCTSTR strFileName )
{
	TCHAR strPath[MAX_PATH]={0};

	StringCchCopy(strPath, MAX_PATH, strFileName);

	if (FALSE == ::PathRemoveFileSpec(strPath)) {
		return L"";
	}
	return strPath;
}

BOOL CMyPath::IsDirectory( LPCTSTR strPath )
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

CString CMyPath::GetShortFileName( const CString &strLongFileName )
{
	int iIndex = strLongFileName.ReverseFind(L'\\');
	return strLongFileName.Right(strLongFileName.GetLength() - iIndex - 1);
}
