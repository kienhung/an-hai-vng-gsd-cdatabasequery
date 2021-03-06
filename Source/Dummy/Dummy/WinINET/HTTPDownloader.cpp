#include "StdAfx.h"
#include "HTTPDownloader.h"
#include "..\Utility\MyUtility.h"


CHTTPDownloader::CHTTPDownloader(void)
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_hSession = NULL;

	m_hConnection = NULL;
}

CHTTPDownloader::~CHTTPDownloader(void)
{
}

BOOL CHTTPDownloader::Download( LPCTSTR strURL, LPCTSTR strFilePath )
{
	BOOL bResult = TRUE;

	try 
	{
		m_hSession = ::InternetOpen(_T(""), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (NULL == m_hSession)
		{
			throw L"InternetOpen is failed";
		}

		TCHAR strHeader[] = L"Accept: */*\r\n\r\n";

		m_hConnection = ::InternetOpenUrl(m_hSession, strURL, strHeader, lstrlen(strHeader), INTERNET_FLAG_PRAGMA_NOCACHE, 0);
		if (NULL == m_hConnection)
		{
			throw L"InternetOpenUrl is failed";
		}
		
		DWORD dwStatusCode = 0;
		DWORD dwLength = sizeof(DWORD);

		HttpQueryInfo(m_hConnection, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER , &dwStatusCode,	&dwLength, NULL);
		
		if (dwStatusCode != HTTP_STATUS_OK)
		{
			throw L"The request didn't complete successfully.";
		}
		
		if (FALSE == SaveFile(strFilePath))
		{
			throw L"SaveFile is failed";
		}

	} 
	catch (LPCTSTR strErrorMessage)
	{
		bResult = FALSE;

		CString strFormatText;
		strFormatText.Format(L"Error: %s with code %u\n", strErrorMessage, GetLastError());

		::OutputDebugString(strFormatText);
	}

	CleanUp();

	return bResult;
}


void CHTTPDownloader::CleanUp()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	if (m_hConnection != NULL) 
	{
		::InternetCloseHandle(m_hConnection);
		m_hConnection = NULL;
	}

	if (m_hSession != NULL)
	{
		::InternetCloseHandle(m_hSession);
		m_hSession = NULL;
	}
}

BOOL CHTTPDownloader::SaveFile( LPCTSTR strFilePath )
{
	if (TRUE == CMyUtility::CheckFileExist(strFilePath))
	{
		DWORD dwAttributes = ::GetFileAttributes(strFilePath);

		if (dwAttributes & FILE_ATTRIBUTE_READONLY) 
		{
			::SetFileAttributes(strFilePath, dwAttributes & ~(FILE_ATTRIBUTE_READONLY));
		}
	}
	
	m_hFile = ::CreateFile(strFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		return FALSE;
	}

	const int MAX_LENGTH = 4096;
	char strBuffer[MAX_LENGTH] = {0};

	DWORD dwByteRead = 0;
	DWORD dwBytesWritten = 0;

	while (TRUE == ::InternetReadFile(m_hConnection, strBuffer, MAX_LENGTH, &dwByteRead) && dwByteRead > 0)
	{
		if (FALSE == ::WriteFile(m_hFile, strBuffer, dwByteRead, &dwBytesWritten, 0))
		{
			return FALSE;
		}
	}
	return TRUE;
}
