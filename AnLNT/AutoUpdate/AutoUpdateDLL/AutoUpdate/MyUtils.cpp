#include "StdAfx.h"
#include "MyUtils.h"
#include <shlwapi.h>
#include <strsafe.h>

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

BOOL CMyUtils::WriteLog( LPCTSTR lpstrData )
{
	TCHAR strModulePath[MAX_PATH]={0};

	if (0 == ::GetModuleFileName(NULL, strModulePath, MAX_PATH)) {
		return FALSE;
	}

	if (FALSE == ::PathRemoveFileSpec(strModulePath)) {
		return FALSE;
	}

	CStdioFile fileWriter;
	CFileException fileException;
	CString strLogPath = CString(strModulePath) + L"\\AutoDetectError.sys";


	if (fileWriter.Open(strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary , &fileException)) {

		fileWriter.SeekToEnd();

		COleDateTime oleDateTime = COleDateTime::GetCurrentTime();
		CString strText;
		strText.Format(L"%s - %s\r\n", oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")), lpstrData);

		fileWriter.WriteString(strText);
		fileWriter.Close();

		return TRUE;
	} 
	return FALSE;
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
