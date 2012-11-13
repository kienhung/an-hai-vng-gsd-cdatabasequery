#pragma once

class CMyUtils
{
public:
	CMyUtils(void);
	virtual ~CMyUtils(void);

	static BOOL FileExists(LPCTSTR lpFilePath);
	static BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists = FALSE);
	static BOOL WriteLog( LPCTSTR lpstrData );
	static BOOL KillWindowProcess(LPCTSTR strClassName, LPCTSTR strWindowName);

	static BOOL KillWindowProcess( HWND hWindow );

};
