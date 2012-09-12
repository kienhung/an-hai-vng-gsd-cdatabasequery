#include "StdAfx.h"
#include "HTTPRequester.h"
#include "..\StringConverter.h"


CHTTPRequester::CHTTPRequester( void )
{
	m_strHeader = _T("Content-Type: application/x-www-form-urlencoded");
}

CHTTPRequester::~CHTTPRequester(void)
{

}

void CHTTPRequester::Initalize()
{
	m_hSession = NULL;
	m_hConnection = NULL;
	m_hRequest = NULL;
}

void CHTTPRequester::CleanUp()
{
	if (m_hSession != NULL) 
	{
		::InternetCloseHandle(m_hSession);
		m_hConnection = NULL;
	}

	if (m_hConnection != NULL) 
	{
		::InternetCloseHandle(m_hConnection);
		m_hConnection = NULL;
	}

	if (m_hRequest != NULL) 
	{
		::InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
	}
}

BOOL CHTTPRequester::PostRequest( LPCTSTR strServer, LPCTSTR strObjectName, LPVOID buffer, size_t uiBufferSize )
{
	Initalize();

	LPCTSTR strArrAcceptTypes[] ={ _T("*/*"), NULL};
	BOOL bResult = TRUE;

	try 
	{
		m_hSession = ::InternetOpen(_T(""), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (NULL == m_hSession)
		{
			throw L"InternetOpen is failed";
		}

		m_hConnection = ::InternetConnect(m_hSession, strServer, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		if (NULL == m_hConnection)
		{
			throw L"InternetConnect is failed";
		}

		m_hRequest = ::HttpOpenRequest(m_hConnection, _T("POST"), strObjectName, NULL, NULL, strArrAcceptTypes, INTERNET_FLAG_PRAGMA_NOCACHE, 0);
		if (NULL == m_hRequest)
		{
			throw L"HttpOpenRequest is failed";
		}

		bResult = ::HttpSendRequest(m_hRequest, m_strHeader, m_strHeader.GetLength(), buffer, uiBufferSize);
	} 
	catch (LPCTSTR strErrorMessage)
	{
		bResult = FALSE;

		CString strFormatText;
		strFormatText.Format(L"Error: %s with code %u", strErrorMessage, GetLastError());

		::OutputDebugString(strFormatText);
	}

	CleanUp();

	return bResult;
}

BOOL CHTTPRequester::PostRequest( LPCTSTR strServer, LPCTSTR strObjectName, LPCTSTR strData )
{

	CStringConverter stringConverter;
	char *strUTF8Data = stringConverter.UnicodeToUTF8(strData);

	if (NULL == strUTF8Data)
	{
		return FALSE;
	}

	return PostRequest(strServer, strObjectName, strUTF8Data, strlen(strUTF8Data));
}

BOOL CHTTPRequester::PostRequest( LPCTSTR strURL, LPCTSTR strData )
{
	const int URL_LENGTH = 255;

	TCHAR strServerName[URL_LENGTH] = {0};
	TCHAR strObjectName[URL_LENGTH] = {0};

	URL_COMPONENTS urlComponents;

	ZeroMemory(&urlComponents, sizeof(urlComponents));
	urlComponents.dwStructSize = sizeof(urlComponents);

	urlComponents.lpszHostName = strServerName;
	urlComponents.dwHostNameLength = URL_LENGTH;

	urlComponents.lpszUrlPath = strObjectName;
	urlComponents.dwUrlPathLength = URL_LENGTH;

	if (FALSE == InternetCrackUrl(strURL, lstrlen(strURL), ICU_ESCAPE, &urlComponents))
	{
		return FALSE;
	}

	return PostRequest(urlComponents.lpszHostName, urlComponents.lpszUrlPath, strData);
}
