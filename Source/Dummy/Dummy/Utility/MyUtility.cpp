#include "StdAfx.h"
#include "MyUtility.h"
#include "XUnzip.h"

CMyUtility::CMyUtility(void)
{
}

CMyUtility::~CMyUtility(void)
{
}

BOOL CMyUtility::UnZip( LPCTSTR wcPathIn, LPCTSTR wcExtractObject, LPCTSTR wcPathOut )
{
	HZIP hz;
	int index, numfile;
	ZIPENTRYW ze = {0};
	TCHAR wcFilePath[MAX_PATH] = {0};
	if(!wcPathIn)
		return FALSE;


	hz = OpenZip((void*)wcPathIn, 0, ZIP_FILENAME);
	if (!hz)
		return FALSE;
	GetZipItem(hz, -1, &ze);
	numfile = ze.index;
	for(index = 0; index < numfile; index++)
	{
		GetZipItem(hz, index, &ze);
		if (!wcExtractObject)
		{
			swprintf(wcFilePath, MAX_PATH - 1, _T("%s\\%s"), wcPathOut, ze.name);
			UnzipItem(hz, index, wcFilePath, 0, ZIP_FILENAME);
		}
		else 
		{
			int len = lstrlen(wcExtractObject);
			if (_tcsnicmp(wcExtractObject, ze.name, len) == 0)
			{
				swprintf(wcFilePath, MAX_PATH - 1, _T("%s\\%s"), wcPathOut, ze.name);
				UnzipItem(hz, index, wcFilePath, 0, ZIP_FILENAME);
				//check to know object need to be extracted is file
				if (!(ze.attr & FILE_ATTRIBUTE_DIRECTORY) && len == lstrlen(ze.name))
					break;
			}
		}
	}
	CloseZip(hz);
	return TRUE;

	return TRUE;
}

BOOL CMyUtility::CreateTempFile( CString &cstrOut )
{
	TCHAR strTempFileName[MAX_PATH];  
	TCHAR strTempPath[MAX_PATH];

	if (0 == ::GetTempPath(MAX_PATH, strTempPath)) {
		return FALSE;
	}

	if (0 == ::GetTempFileName(strTempPath, L"hkt", 0,  strTempFileName)) {
		return FALSE;
	}

	cstrOut = strTempFileName;
	return TRUE;
}

BOOL CMyUtility::GetModifyTime( LPCTSTR strFileName, FILETIME &fileTime )
{

	HANDLE hFile;

	hFile = CreateFile(     strFileName, 
							GENERIC_READ, 
							FILE_SHARE_READ, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
		return FALSE;

	if (!GetFileTime(hFile, NULL, NULL, &fileTime))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);

	return TRUE;

}

BOOL CMyUtility::QueryMasterModifyTime( LPCTSTR strMasterFile, SYSTEMTIME *lpSysTime )
{

	// Clear output buffer
	SecureZeroMemory(lpSysTime, sizeof(SYSTEMTIME));

	DeleteUrlCacheEntry(strMasterFile);

	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) 
		return FALSE;

	// Open the resource from server
	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, strMasterFile, NULL, 0, 0, 0);
	if (!hInternetFile)
	{
		InternetCloseHandle(hInternetSession);
		return FALSE;
	}

	// Query last modify date and time
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_LAST_MODIFIED | HTTP_QUERY_FLAG_SYSTEMTIME, lpSysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetFile);
		InternetCloseHandle(hInternetSession);
		return FALSE;
	}

	// Clean up...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);
	return TRUE;

}

BOOL CMyUtility::SetModifyTime( LPCTSTR strFileName, const FILETIME &modifyTime )
{

	HANDLE      hFile;
	BOOL  bRet;

	hFile = CreateFile(     strFileName, 
		FILE_WRITE_ATTRIBUTES, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
		return FALSE;

	bRet = SetFileTime(hFile, NULL, NULL, &modifyTime);
	CloseHandle(hFile);

	return bRet;

}

BOOL CMyUtility::CheckFileExist( LPCTSTR strFilePath )
{
	WIN32_FIND_DATA FindFileData;

	HANDLE hFind = ::FindFirstFile(strFilePath, &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	::FindClose(hFind);
	return TRUE;
}

BOOL CMyUtility::Decode( LPCTSTR strSource, LPCTSTR strDest )
{

	return TRUE;
}

void CMyUtility::StringTrim( string &str )
{

	string::size_type pos = str.find_last_not_of(' ');
	if(pos != string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if(pos != string::npos) str.erase(0, pos);
	}
	else str.erase(str.begin(), str.end());
}
