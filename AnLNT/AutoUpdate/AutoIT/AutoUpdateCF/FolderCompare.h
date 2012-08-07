#pragma once
#include "FolderProcesser.h"

class CFolderCompare
	: public CFolderProcesser
{
protected:
	CString m_strNewSource;
	CString m_strOldSource;

	HANDLE m_hResultFile;
	HANDLE m_hTempFile;
public:

	CFolderCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);

	virtual ~CFolderCompare(void);
	BOOL Compare(LPCTSTR strResultFilePath);

protected:
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	BOOL CheckFileExist(LPCTSTR strFileName);
	BOOL CheckSum(LPCTSTR strFirstFile, LPCTSTR strSecondFile);
	BOOL CreateResultFile(LPCTSTR strFileName);
	BOOL CreateTempResultFile();

	BOOL WriteFile (LPCTSTR strFileName, HANDLE hFile);
	BOOL CreateFinalResult();
};
