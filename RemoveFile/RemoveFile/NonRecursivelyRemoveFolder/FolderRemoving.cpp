#include "StdAfx.h"
#include "FolderRemoving.h"

CFolderRemoving::CFolderRemoving(void)
{
}

CFolderRemoving::~CFolderRemoving(void)
{
	while (!m_stackItems.empty()) {

		TCHAR *ptcPath = m_stackItems.top();
		
		if (ptcPath != NULL) {
			delete ptcPath;
			ptcPath = NULL;
			m_stackItems.pop();
		}
	}
	
	while (!m_stackDirectories.empty()) {

		TCHAR *ptcPath = m_stackDirectories.top();

		if (ptcPath != NULL) {
			delete ptcPath;
			ptcPath = NULL;
			m_stackDirectories.pop();
		}
	}
}

BOOL CFolderRemoving::IsDirectory(const TCHAR strPath[]) {

	DWORD dwAttribute = GetFileAttributes(strPath);

	if (FILE_ATTRIBUTE_DIRECTORY  == dwAttribute) {
		return TRUE;
	}
	return FALSE;
}

BOOL CFolderRemoving::IsFile(const TCHAR strPath[]) {

	DWORD dwAttribute = GetFileAttributes(strPath);

	if (FILE_ATTRIBUTE_ARCHIVE  == dwAttribute) {
		return TRUE;
	}
	return FALSE;
}

BOOL CFolderRemoving::NonRecursivelyRemove(const TCHAR strPath[]) {

	if (lstrlen(strPath) + 1 > MAX_PATH) {
		return FALSE;
	}
	size_t uiLength = lstrlen(strPath) + 1;
	TCHAR *ptcPath = new TCHAR[uiLength];

	_tcscpy_s(ptcPath, uiLength, strPath);
	m_stackItems.push(ptcPath);

	while (!m_stackItems.empty()) {
		
		ptcPath = m_stackItems.top();
		m_stackItems.pop();

		if (IsFile(ptcPath) == TRUE) {

			::OutputDebugString(ptcPath);
			::OutputDebugStringA("\n");
			delete ptcPath;
			ptcPath = NULL;

		} else if(IsDirectory(ptcPath) == FALSE) {
			
			
		}

	}

	return FALSE;
}

void CFolderRemoving::AddChildsToItemsStack(const TCHAR strPath[]) {

	size_t uiLength = lstrlen(strPath) + 3;
	TCHAR *ptcFirstFile = new TCHAR[uiLength];
	
	_tcscpy_s(ptcFirstFile, uiLength, 

	//ZeroMemory(strDir, MAX_PATH);
}