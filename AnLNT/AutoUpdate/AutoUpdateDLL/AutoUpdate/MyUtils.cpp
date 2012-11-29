#include "StdAfx.h"
#include "MyUtils.h"
#include <shlwapi.h>
#include <strsafe.h>
#include "GlobalClass.h"
#include "WindowFinder.h"

CMyUtils::CMyUtils(void)
{
}

CMyUtils::~CMyUtils(void)
{
}

BOOL CMyUtils::CopyFile( LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists /*= FALSE*/ )
{
	if (bFailIfExists == FALSE && FileExists(lpNewFileName))
	{
		DWORD dwAttr = GetFileAttributes(lpNewFileName);
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes(lpNewFileName, FILE_ATTRIBUTE_NORMAL);
	}

	return ::CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists);
}

BOOL CMyUtils::FileExists( LPCTSTR lpFilePath )
{
	CFileFind findFile;

	if (findFile.FindFile(lpFilePath))
	{
		findFile.Close();
		return TRUE;
	}
	return FALSE;
}

BOOL CMyUtils::WriteErrorLog( LPCTSTR lpstrData )
{
	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, lpstrData);
	return TRUE;
}

BOOL CMyUtils::KillWindowProcess( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	HWND hWindow = ::FindWindow(strClassName, strWindowName);
	if (NULL == hWindow) {
		return FALSE;
	}

	if (FALSE == CMyUtils::KillWindowProcess(hWindow))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMyUtils::KillWindowProcess( HWND hWindow )
{

	DWORD dwProcessID;

	GetWindowThreadProcessId(hWindow, &dwProcessID);

	HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);

	if (NULL == hProcess) {
		return TRUE;
	}

	if (FALSE == ::TerminateProcess(hProcess, 0)) {
		return TRUE;
	} 
	::WaitForSingleObject(hProcess, INFINITE);
	::CloseHandle(hProcess);

	DWORD dwWait = 5000;
	::Sleep(dwWait);

	return TRUE;
}

BOOL CMyUtils::IsFileInDirectory( LPCTSTR strFileName, LPCTSTR strDirectoryName )
{
	TCHAR strTempPath[MAX_PATH] = {0};
	HRESULT hResult = ::StringCchCopy(strTempPath, MAX_PATH, strFileName);
	if (hResult != S_OK)
	{
		return FALSE;
	}
	if (FALSE == ::PathRemoveFileSpec(strTempPath))
	{
		return FALSE;
	}
	PTSTR strTempDirectoryName = ::PathFindFileName(strTempPath);
	if (lstrcmpi(strDirectoryName, strTempDirectoryName) != 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMyUtils::DeleteFile( LPCTSTR lpFileName )
{
	if (FileExists(lpFileName))
	{
		DWORD dwAttr = GetFileAttributes(lpFileName);
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes(lpFileName, FILE_ATTRIBUTE_NORMAL);
		return ::DeleteFile(lpFileName);
	}

	return FALSE;
}

BOOL CMyUtils::DeleteDir( LPCTSTR lpDirPath )
{
	CFileFind	finder;
	BOOL		bFind;
	TCHAR		strFindPath[MAX_PATH];

	_stprintf(strFindPath, _T("%s\\*"), lpDirPath);
	bFind = finder.FindFile(strFindPath);
	while (bFind)   
	{
		bFind = finder.FindNextFile();
		if (!finder.IsDirectory())
		{
			if (!CMyUtils::DeleteFile(finder.GetFilePath()))
			{
				finder.Close();
				return FALSE;
			}
		}
		else if (!finder.IsDots())
		{
			if (!DeleteDir(finder.GetFilePath()))
			{
				finder.Close();
				return FALSE;
			}
		}
	}
	finder.Close();

	return RemoveDirectory(lpDirPath);
}

void CMyUtils::SimulateLeftMouseClick( HWND hWnd, int x, int y )
{
	::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::PostMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
	::PostMessage(hWnd, WM_LBUTTONUP, 00000, MAKELPARAM(x, y));
}

void CMyUtils::SimulateLeftMouseClick( const vector<HWND> &vWnd, int x, int y )
{
	for (size_t i = 0; i < vWnd.size(); i++)
	{
		SimulateLeftMouseClick(vWnd[i], x, y);
	}
}

wchar_t* CMyUtils::ConvertUTF8ToWideChar( const char *strUTF8 )
{
	wchar_t	*strWideChar = NULL;
	int		iLen,
		iNumChar = 0;

	iLen = strlen(strUTF8);
	if (iLen <= 0)
	{
		strWideChar = new wchar_t[1];
		if (strWideChar)
			strWideChar[0] = 0;
	}
	else
	{
		// Get the required buffer size for WideChar string (the 6th parameter is set to 0)
		iNumChar = MultiByteToWideChar(CP_UTF8, 0, strUTF8, iLen, NULL, 0);
		if (iNumChar > 0)
		{
			strWideChar = new wchar_t[iNumChar + 1];
			if (strWideChar)
			{
				memset(strWideChar, 0, (iNumChar + 1)*2);
				iNumChar = MultiByteToWideChar(CP_UTF8, 0, strUTF8, iLen, strWideChar, iNumChar);
				if (iNumChar <= 0)
				{
					// Mapping string doesn't succeed
					delete []strWideChar;
					strWideChar = NULL;
				}
			}
		}
	}

	return strWideChar;
}

char* CMyUtils::ConvertWideCharToUTF8( const wchar_t *strWideChar )
{

	char	*strUTF8 = NULL;
	int		iLen,
		iNumByte = 0;

	iLen = wcslen(strWideChar);
	if (iLen <= 0)
	{
		strUTF8 = new char[1];
		if (strUTF8)
			strUTF8[0] = 0;
	}
	else
	{
		// Get the required buffer size for UTF8 string (the 6th parameter is set to 0)
		iNumByte = WideCharToMultiByte(CP_UTF8, 0, strWideChar, iLen, NULL, 0, NULL, NULL);
		if (iNumByte > 0)
		{
			strUTF8 = new char[iNumByte + 1];
			if (strUTF8)
			{
				memset(strUTF8, 0, iNumByte + 1);
				iNumByte = WideCharToMultiByte(CP_UTF8, 0, strWideChar, iLen, strUTF8, iNumByte, NULL, NULL);
				if (iNumByte <= 0)
				{
					// Mapping string doesn't succeed
					delete []strUTF8;
					strUTF8 = NULL;
				}
			}
		}
	}

	return strUTF8;
}

void CMyUtils::KillWindowProcessEx( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	CWindowFinder windowFinder;
	vector<HWND> listMainWnd = windowFinder.GetListWindow(strClassName, strWindowName);
	
	for (size_t i = 0; i < listMainWnd.size(); i++)
	{
		KillWindowProcess(listMainWnd[i]);
	}
}

void CMyUtils::KillProcess( PROCESS_INFORMATION *processInfo )
{
	if (FALSE == ::TerminateThread(processInfo->hThread, 0))
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_WARN, L"Unable to kill %u thread", processInfo->dwThreadId);
	}
	::WaitForSingleObject(processInfo->hThread, INFINITE);
	if (FALSE == ::TerminateProcess(processInfo->hProcess, 0))
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_WARN, L"Unable to kill %u thread", processInfo->dwProcessId);
	}
	::WaitForSingleObject(processInfo->hProcess, INFINITE);
	DWORD dwWait = 5000;
	::Sleep(dwWait);
}
