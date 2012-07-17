#include "StdAfx.h"
#include "RemoveFolder.h"

BOOL RemoveFolder (__in  LPCTSTR pstrPathName) {

	DWORD dwAttribute = GetFileAttributes(pstrPathName);

	if (FILE_ATTRIBUTE_ARCHIVE  == dwAttribute) {
		return ::DeleteFile(pstrPathName);
	}

	if (FILE_ATTRIBUTE_DIRECTORY == dwAttribute ) {

		TCHAR strDir[MAX_PATH];
		ZeroMemory(strDir, MAX_PATH);

		_tcscpy_s(strDir, MAX_PATH, pstrPathName);
		_tcscat_s(strDir, MAX_PATH, _T("\\*"));

		WIN32_FIND_DATA findFileData;
		HANDLE hFind = ::FindFirstFile(strDir, &findFileData);

		if (INVALID_HANDLE_VALUE == hFind) {
			return FALSE;
		}

		BOOL bFlag = TRUE;

		do {
			if (lstrcmpi(findFileData.cFileName, _T(".")) != 0
				&& lstrcmpi(findFileData.cFileName, _T("..")) != 0) {

				ZeroMemory(strDir, MAX_PATH);

				_tcscpy_s(strDir, MAX_PATH, pstrPathName);
				_tcscat_s(strDir, MAX_PATH, _T("\\"));
				_tcscat_s(strDir, MAX_PATH, findFileData.cFileName);

				bFlag = ::RemoveFolder(strDir);
			}	

		} while (::FindNextFile(hFind, &findFileData) != 0 && TRUE == bFlag);

		::FindClose(hFind);

		if (FALSE == bFlag) {
			return FALSE;
		}
		return ::RemoveDirectory(pstrPathName);
	}

	return FALSE;
}