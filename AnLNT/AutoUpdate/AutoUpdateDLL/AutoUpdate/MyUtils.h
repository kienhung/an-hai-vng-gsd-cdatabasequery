#pragma once

class CMyUtils
{
public:
	CMyUtils(void);
	virtual ~CMyUtils(void);

	static BOOL FileExists(LPCTSTR lpFilePath);
	static BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists = FALSE);
	static BOOL WriteErrorLog( LPCTSTR lpstrData );
	static BOOL KillWindowProcess(LPCTSTR strClassName, LPCTSTR strWindowName);

	static BOOL KillWindowProcess( HWND hWindow );
	static BOOL IsFileInDirectory(LPCTSTR strFileName, LPCTSTR strDirectoryName);
	static BOOL DeleteFile(LPCTSTR lpFileName);
	static BOOL DeleteDir(LPCTSTR lpDirPath);
};
