#include "StdAfx.h"
#include "FolderCloner.h"
#include "FileServices.h"
#include "FolderRemoving.h"
#include <strsafe.h>
#include "MyPath.h"

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

	CMyPath myPath;

	if (FALSE == myPath.IsDirectory(strRoot)) {
		return FALSE;
	}

	if (FALSE == myPath.IsDirectory(m_strDest)) {
		return FALSE;
	}

	if (FALSE == Process(strRoot)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CFolderCloner::PreProcessFoler( LPCTSTR strFolderName )
{

	CMyPath myPath;
	CString strPath = myPath.TransferSourcePath(m_strSource, m_strDest, strFolderName);

	if (TRUE == myPath.IsDirectory(strPath)) {
		return TRUE;
	}

	if (FALSE == ::CreateDirectory(strPath, NULL)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CFolderCloner::ProcessFile( LPCTSTR strFileName )
{

	CMyPath myPath;
	CString strPath = myPath.TransferSourcePath(m_strSource, m_strDest, strFileName);

	if (FALSE == ::CopyFile(strFileName, strPath, FALSE)) {
		return FALSE;
	}
	return TRUE;
}
