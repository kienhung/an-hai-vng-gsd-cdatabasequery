#pragma once

class CMyUtils
{
public:
	CMyUtils(void);
	~CMyUtils(void);

	static BOOL InitGlobalVariable();
	
	// functions about string
	static char* ConvertWideCharToUTF8(const wchar_t *strWideChar);
	static char* ConvertWideCharToANSI(const wchar_t *strWideChar);
	static wchar_t* ConvertUTF8ToWideChar(const char *strUTF8);
	
	// functions about file and directory
	static BOOL FileExists(LPCTSTR lpFilePath);
	static BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists = FALSE);
	static BOOL MoveFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags = MOVEFILE_REPLACE_EXISTING);
	static BOOL DeleteFile(LPCTSTR lpFileName);
	static BOOL CreateDir(LPCTSTR lpDirPath);
	static BOOL DeleteDir(LPCTSTR lpDirPath);
	static BOOL GetTempFilePath(TCHAR strFilePath[]);
	static BOOL GetSpecialFolder(int nFolder, TCHAR strFolder[MAX_PATH]);
	
	// functions about windows right
	static BOOL EnableDebugPrivNT(VOID);

	// common
	static BOOL CheckServerVersion(LPCTSTR strVersion, int iVersion, int iMiddle, int iTail);
};
