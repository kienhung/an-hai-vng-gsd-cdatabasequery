#pragma once
#include <vector>
using namespace std;

class CMyUtils
{
public:
	CMyUtils(void);
	virtual ~CMyUtils(void);

	static char* ConvertWideCharToUTF8(const wchar_t *strWideChar);
	static wchar_t* ConvertUTF8ToWideChar(const char *strUTF8);

	static BOOL FileExists(LPCTSTR lpFilePath);
	static BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists = FALSE);
	static BOOL WriteErrorLog( LPCTSTR lpstrData );
	static BOOL KillWindowProcess(LPCTSTR strClassName, LPCTSTR strWindowName);

	static BOOL KillWindowProcess( HWND hWindow );
	static BOOL IsFileInDirectory(LPCTSTR strFileName, LPCTSTR strDirectoryName);
	static BOOL DeleteFile(LPCTSTR lpFileName);
	static BOOL DeleteDir(LPCTSTR lpDirPath);
	static void SimulateLeftMouseClick(HWND hWnd, int x, int y);
	static void SimulateLeftMouseClick(const vector<HWND> &vWnd, int x, int y);
	static void KillWindowProcessEx(LPCTSTR strClassName, LPCTSTR strWindowName);
	static void KillProcess(PROCESS_INFORMATION *processInfo);
	static void ReadINISectionNames(LPCTSTR strINIPath, CStringArray &arrResult);
};
