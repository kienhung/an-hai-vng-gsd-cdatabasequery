#include "StdAfx.h"
#include "FolderRemoving.h"
#include <strsafe.h>

CFolderRemoving::CFolderRemoving(void)
{
}

CFolderRemoving::~CFolderRemoving(void)
{

}

BOOL CFolderRemoving::Remove( const TCHAR strPath[] )
{

	if (FALSE == Process(strPath)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CFolderRemoving::ProcessFile( LPCTSTR strFileName )
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

BOOL CFolderRemoving::PostProcessFolder( LPCTSTR strFolderName )
{

	if (FALSE == RemoveDirectory(strFolderName)) {
		return FALSE;
	}

	return TRUE;
}

