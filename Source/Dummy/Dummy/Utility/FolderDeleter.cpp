#include "StdAfx.h"
#include "FolderDeleter.h"
#include <strsafe.h>

CFolderDeleter::CFolderDeleter(void)
{
}

CFolderDeleter::~CFolderDeleter(void)
{

}

BOOL CFolderDeleter::Delete( const TCHAR strPath[] )
{
	if (FALSE == Process(strPath)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CFolderDeleter::ProcessFile( LPCTSTR strFileName )
{

	DWORD dwAttributes = ::GetFileAttributes(strFileName);

	if (dwAttributes & FILE_ATTRIBUTE_READONLY) {
		::SetFileAttributes(strFileName, dwAttributes & ~(FILE_ATTRIBUTE_READONLY));
	}

	if (FALSE == ::DeleteFile(strFileName)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CFolderDeleter::PostProcessFolder( LPCTSTR strFolderName )
{

	if (FALSE == RemoveDirectory(strFolderName)) {
		return FALSE;
	}

	return TRUE;
}

