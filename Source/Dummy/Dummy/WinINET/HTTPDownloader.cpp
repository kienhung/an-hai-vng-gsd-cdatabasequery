#include "StdAfx.h"
#include "HTTPDownloader.h"


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
		m_hSession = ::InternetOpen(_T("VNG"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
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
