#include "StdAfx.h"
#include "FolderProcesser.h"
#include <strsafe.h>
#include "PathUtility.h"

CFolderProcesser::CFolderProcesser(void)
{
}

CFolderProcesser::~CFolderProcesser(void)
{
}

BOOL CFolderProcesser::ProcessFile( LPCTSTR strFileName )
{
	return TRUE;
}

BOOL CFolderProcesser::Process( LPCTSTR strSourcePath )
{

	if (FALSE == CPathUtility::IsPathDirectory(strSourcePath)) {
		return ProcessFile(strSourcePath);
	}

	if (FALSE == PreProcessFoler(strSourcePath)) {
		return FALSE;
	}

	if (FALSE == ProcessFolder(strSourcePath)) {
		return FALSE;
	}
	return PostProcessFolder(strSourcePath);
}

HANDLE CFolderProcesser::GetFindHandle( LPCTSTR strFolderName, WIN32_FIND_DATA *pFindFileData )
{
	size_t uiLength;

	uiLength = lstrlen(strFolderName) + lstrlen(_T("\\*")) + 1;
	TCHAR *ptcFirstFilePath = new TCHAR[uiLength];

	StringCchPrintf(ptcFirstFilePath, uiLength, _T("%s\\*"), strFolderName);

	HANDLE hFind = ::FindFirstFile(ptcFirstFilePath, pFindFileData);

	delete ptcFirstFilePath;
	return hFind;
}

BOOL CFolderProcesser::ProcessFolder( LPCTSTR strFolderName )
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = GetFindHandle(strFolderName, &findFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	BOOL bFlag = TRUE;

	do {
		if (lstrcmpi(findFileData.cFileName, _T(".")) != 0
			&& lstrcmpi(findFileData.cFileName, _T("..")) != 0) {

				size_t uiLength = lstrlen(strFolderName) + lstrlen(_T("\\")) + lstrlen(findFileData.cFileName) + 1;
				TCHAR *ptcChildPath = new TCHAR[uiLength];

				StringCchPrintf(ptcChildPath, uiLength, _T("%s\\%s"), strFolderName, findFileData.cFileName);

				bFlag = Process(ptcChildPath);

				delete ptcChildPath;
		}	

	} while (::FindNextFile(hFind, &findFileData) != 0 && TRUE == bFlag);

	::FindClose(hFind);

	if (FALSE == bFlag) {
		return FALSE;
	}
	return TRUE;
}

BOOL CFolderProcesser::PreProcessFoler( LPCTSTR strFolderName )
{
	return TRUE;
}

BOOL CFolderProcesser::PostProcessFolder( LPCTSTR strFolderName )
{

	return TRUE;
}

