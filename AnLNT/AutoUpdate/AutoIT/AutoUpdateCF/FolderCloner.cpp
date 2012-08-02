#include "StdAfx.h"
#include "FolderCloner.h"
#include "FileServices.h"
#include "FolderRemoving.h"
#include <strsafe.h>

CFolderCloner::CFolderCloner( LPCTSTR strSource, LPCTSTR strDest, LPCTSTR strFolderName )
{
	
	m_strSource = strSource;
	m_strDest = strDest;
	m_strFolderName = strFolderName;

}

CFolderCloner::~CFolderCloner(void)
{
}

BOOL CFolderCloner::Clone()
{

	CString strRoot = m_strSource + CString(L"\\") + m_strFolderName;

	if (FALSE == RecursivelyCopyFile(strRoot)) {
		return FALSE;
	}
	return TRUE;
}

BOOL CFolderCloner::RecursivelyCopyFile( LPCTSTR strFileName )
{
	CFileServices fileServices;

	CString strText;

	if (FALSE == fileServices.IsDirectory(strFileName)) {
		if (FALSE == CustomCopyFile(strFileName)) {
			return FALSE;
		}
		return TRUE;
	}

	if (FALSE == CustomCreateDirectory(strFileName)) {
		return FALSE;
	}

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = GetFindHandle(strFileName, &findFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	BOOL bFlag = TRUE;
	do {
		if (lstrcmpi(findFileData.cFileName, _T(".")) != 0
			&& lstrcmpi(findFileData.cFileName, _T("..")) != 0) {

				size_t uiLength = lstrlen(strFileName) + lstrlen(_T("\\")) + lstrlen(findFileData.cFileName) + 1;
				TCHAR *ptcChildPath = new TCHAR[uiLength];

				StringCchPrintf(ptcChildPath, uiLength, _T("%s\\%s"), strFileName, findFileData.cFileName);

				bFlag = RecursivelyCopyFile(ptcChildPath);

				delete ptcChildPath;
		}	

	} while (::FindNextFile(hFind, &findFileData) != 0 && TRUE == bFlag);

	::FindClose(hFind);

	if (FALSE == bFlag) {
		return FALSE;
	}

	return TRUE;
}

HANDLE CFolderCloner::GetFindHandle( LPCTSTR strFileName, WIN32_FIND_DATA *pFindFileData)
{
	size_t uiLength;

	uiLength = lstrlen(strFileName) + lstrlen(_T("\\*")) + 1;
	TCHAR *ptcFirstFilePath = new TCHAR[uiLength];

	StringCchPrintf(ptcFirstFilePath, uiLength, _T("%s\\*"), strFileName);

	HANDLE hFind = ::FindFirstFile(ptcFirstFilePath, pFindFileData);

	delete ptcFirstFilePath;
	return hFind;
}

BOOL CFolderCloner::CustomCreateDirectory( LPCTSTR strFileName )
{

	CString strPath = strFileName;
	strPath.Replace(m_strSource, m_strDest);
	
	CFileServices fileServices;
	return fileServices.CustomCreateDirectory(strPath);
}

BOOL CFolderCloner::RemoveFolderIfExist()
{
	CFileServices fileServices;

	CString strLongDestName = m_strDest + CString("\\") +  m_strFolderName;

	if (fileServices.IsDirectory(strLongDestName)) {
		CFolderRemoving folderRemoving;
		return folderRemoving.RemoveFolder(strLongDestName);
	
	}
	return TRUE;
}

BOOL CFolderCloner::CustomCopyFile( LPCTSTR strFileName )
{

	CString strPath = strFileName;
	strPath.Replace(m_strSource, m_strDest);

	return 	CopyFile(strFileName, strPath, FALSE);
}
