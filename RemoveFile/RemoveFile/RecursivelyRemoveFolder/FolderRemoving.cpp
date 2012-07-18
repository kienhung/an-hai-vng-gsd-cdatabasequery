#include "StdAfx.h"
#include "FolderRemoving.h"
#include <strsafe.h>

CFolderRemoving::CFolderRemoving(void)
{
}

CFolderRemoving::~CFolderRemoving(void)
{

}

BOOL CFolderRemoving::IsDirectory(const TCHAR strPath[]) {

	if (::GetFileAttributes(strPath) & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}
	return FALSE;
}

BOOL CFolderRemoving::RemoveFile(const TCHAR strPath[]) {

	DWORD dwAttributes = ::GetFileAttributes(strPath);

	if (dwAttributes & FILE_ATTRIBUTE_READONLY) {
		::SetFileAttributes(strPath, dwAttributes & ~(FILE_ATTRIBUTE_READONLY));
	}

	return ::DeleteFile(strPath);
}

BOOL CFolderRemoving::RemoveFolder(const TCHAR strFolderPath[]) {

	if (IsDirectory(strFolderPath) == FALSE) {
		return RemoveFile(strFolderPath);
	}
	size_t uiLength;

	uiLength = lstrlen(strFolderPath) + lstrlen(_T("\\*")) + 1;
	TCHAR *ptcFirstFilePath = new TCHAR[uiLength];

	StringCchPrintf(ptcFirstFilePath, uiLength, _T("%s\\*"), strFolderPath);

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = ::FindFirstFile(ptcFirstFilePath, &findFileData);

	delete ptcFirstFilePath;
	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	BOOL bFlag = TRUE;

	do {
		if (lstrcmpi(findFileData.cFileName, _T(".")) != 0
			&& lstrcmpi(findFileData.cFileName, _T("..")) != 0) {

				uiLength = lstrlen(strFolderPath) + lstrlen(_T("\\")) + lstrlen(findFileData.cFileName) + 1;
				TCHAR *ptcChildPath = new TCHAR[uiLength];
				
				StringCchPrintf(ptcChildPath, uiLength, _T("%s\\%s"), strFolderPath, findFileData.cFileName);

				bFlag = RemoveFolder(ptcChildPath);

				delete ptcChildPath;
		}	

	} while (::FindNextFile(hFind, &findFileData) != 0 && TRUE == bFlag);

	::FindClose(hFind);

	if (FALSE == bFlag) {
		return FALSE;
	}

	return ::RemoveDirectory(strFolderPath);
}


