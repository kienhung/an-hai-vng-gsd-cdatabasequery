#include "StdAfx.h"
#include "MyUtils.h"
#include "token.h"

CMyUtils::CMyUtils(void)
{
}

CMyUtils::~CMyUtils(void)
{
}

/****************************************************************************
* Description: Convert a wide character string to a UTF8 string. 
* Input:	const wchar_t *strWideChar:	The wide character string to convert.
* Output:	None.
* Return:	The UTF8 string if successful; otherwise NULL
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
char* CMyUtils::ConvertWideCharToUTF8(const wchar_t *strWideChar)
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

/****************************************************************************
* Description: Convert a wide character string to an ANSI string. 
* Input:	const wchar_t *strWideChar:	The wide character string to convert.
* Output:	None.
* Return:	The ANSI string if successful; otherwise NULL
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
char* CMyUtils::ConvertWideCharToANSI(const wchar_t *strWideChar)
{
	char	*strANSI = NULL;
	int		iLen,
			iNumByte = 0;

	iLen = wcslen(strWideChar);
	if (iLen <= 0)
	{
		strANSI = new char[1];
		if (strANSI)
			strANSI[0] = 0;
	}
	else
	{
		// Get the required buffer size for ANSI string (the 6th parameter is set to 0)
		iNumByte = WideCharToMultiByte(CP_ACP, 0, strWideChar, iLen, NULL, 0, NULL, NULL);
		if (iNumByte > 0)
		{
			strANSI = new char[iNumByte + 1];
			if (strANSI)
			{
				memset(strANSI, 0, iNumByte + 1);
				iNumByte = WideCharToMultiByte(CP_ACP, 0, strWideChar, iLen, strANSI, iNumByte, NULL, NULL);
				if (iNumByte <= 0)
				{
					// Mapping string doesn't succeed
					delete []strANSI;
					strANSI = NULL;
				}
			}
		}
	}

	return strANSI;
}

/****************************************************************************
* Description: Convert a UTF8 string to a wide character string. 
* Input:	const char *strUTF8:	The UTF8 string to convert.
* Output:	None.
* Return:	The wide character string if successful; otherwise NULL
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
wchar_t* CMyUtils::ConvertUTF8ToWideChar(const char *strUTF8)
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

BOOL CMyUtils::FileExists(LPCTSTR lpFilePath)
{
	CFileFind findFile;

	if (findFile.FindFile(lpFilePath))
	{
		findFile.Close();
		return TRUE;
	}
	return FALSE;
}

BOOL CMyUtils::CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists)
{
	if (bFailIfExists == FALSE && FileExists(lpNewFileName))
	{
		DWORD dwAttr = GetFileAttributes(lpNewFileName);
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes(lpNewFileName, FILE_ATTRIBUTE_NORMAL);
	}

	return ::CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists);
}

BOOL CMyUtils::MoveFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags)
{
	if ((dwFlags & MOVEFILE_REPLACE_EXISTING) && FileExists(lpNewFileName))
	{
		DWORD dwAttr = GetFileAttributes(lpNewFileName);
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes(lpNewFileName, FILE_ATTRIBUTE_NORMAL);
	}

	return ::MoveFileEx(lpExistingFileName, lpNewFileName, dwFlags);
}

BOOL CMyUtils::DeleteFile(LPCTSTR lpFileName)
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

BOOL CMyUtils::CreateDir(LPCTSTR lpDirPath)
{
	WIN32_FIND_DATA w32fd = {0};
	HANDLE			hFind = INVALID_HANDLE_VALUE; 
	TCHAR			szPath[MAX_PATH],
					szTmpPath[MAX_PATH],
					*p;
	int				len;

	_tcscpy(szPath, lpDirPath);
	len = _tcslen(szPath);

	while (len > 0 && szPath[len - 1] == '\\')
	{
		szPath[--len] = 0;
	}

	if (len <= 0)
		return FALSE;

	if (szPath[len - 1] == ':')	// drive
	{
		UINT nType = GetDriveType(szPath);
		if (DRIVE_FIXED == nType)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		hFind = FindFirstFile(szPath, &w32fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);
			if ((w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}

	p = _tcsrchr(szPath, '\\');
	if (p)
	{
		len = p - szPath;
		_tcsncpy(szTmpPath, szPath, len);
		szTmpPath[len] = 0;
		if (!CreateDir(szTmpPath))
			return FALSE;
	}

	return CreateDirectory(szPath, NULL);
}

BOOL CMyUtils::DeleteDir(LPCTSTR lpDirPath)
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
			if (!DeleteFile(finder.GetFilePath()))
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

BOOL CMyUtils::GetTempFilePath(TCHAR strFilePath[])
{
	TCHAR strTempDir[MAX_PATH] = {0};

	if (!GetTempPath(MAX_PATH, strTempDir))
		return FALSE;

	return GetTempFileName(strTempDir, _T("TCK"), 0, strFilePath);
}

BOOL CMyUtils::GetSpecialFolder(int nFolder, TCHAR strFolder[MAX_PATH])
{
	TCHAR	*p = NULL;
	
	LPITEMIDLIST	pidl = NULL;
	IMalloc	*pMalloc = NULL;
	BOOL	bRet = FALSE;
	
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		pMalloc->AddRef();
		SHGetSpecialFolderLocation(NULL, nFolder, &pidl);
		
		if (pidl)
        {                      
			bRet = SHGetPathFromIDList(pidl, strFolder);
            // Free the PIDL returned by SHGetSpecialFolderLocation.
           pMalloc->Free(pidl);
        }

        // Release the IMalloc interface.
        pMalloc->Release();
    }

	return bRet;
}

BOOL CMyUtils::EnableDebugPrivNT(VOID)
{
	HANDLE hToken;
	LUID DebugValue;
	TOKEN_PRIVILEGES tkp;


	//
	// Retrieve a handle of the access token
	//
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) 
	{
		return FALSE;
	}

	//
	// Enable the SE_DEBUG_NAME privilege
	//
	if (!LookupPrivilegeValue(NULL,
		SE_DEBUG_NAME,
		&DebugValue)) 
	{
		return FALSE;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = DebugValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(	hToken,
							FALSE,
							&tkp,
							sizeof(TOKEN_PRIVILEGES),
							(PTOKEN_PRIVILEGES) NULL,
							(PDWORD) NULL);

	//
	// The return value of AdjustTokenPrivileges can't be tested
	//
	if (GetLastError() != ERROR_SUCCESS) 
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMyUtils::CheckServerVersion(LPCTSTR strVersion, int iVersion, int iMiddle, int iTail)
{
	int		iVersionSever = 0,
			iMiddleServer = 0,
			iTailServer = 0;
	CToken	token(strVersion, _T("."));

	iVersionSever = _ttoi(token.GetNextToken());
	iMiddleServer = _ttoi(token.GetNextToken());
	iTailServer = _ttoi(token.GetNextToken());

	if (iVersionSever > iVersion)
	{
		return TRUE;
	}
	else if (iVersionSever == iVersion)
	{
		if (iMiddleServer > iMiddle)
		{
			return TRUE;
		}
		else if (iMiddleServer == iMiddle)
		{
			if (iTailServer >= iTail)
			{	
				return TRUE;
			}
		}
	}
	
	return FALSE;
}
