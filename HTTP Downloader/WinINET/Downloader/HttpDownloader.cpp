#include "StdAfx.h"
#include "HttpDownloader.h"

CHttpDownloader::~CHttpDownloader(void)
{
	CleanUp();
}

void CHttpDownloader::CleanUp(){

	if (NULL != m_pHttpFile) {
		delete m_pHttpFile;
		m_pHttpFile = NULL;
	}

	if (NULL != m_pHttpConnection) {
		delete m_pHttpConnection;
		m_pHttpConnection = NULL;
	}
}

bool CHttpDownloader::DownLoad() {
	
	if (NULL != m_pHttpFile) {
		delete[] m_pHttpFile;
	}

	m_pHttpFile = m_pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, m_strFileName);
	m_pHttpFile->SendRequest();//throw CInternetException

	DWORD dwStatusCode;
	m_pHttpFile->QueryInfoStatusCode(dwStatusCode);

	if (200 == dwStatusCode) {

		const int MAXBUF = 1024;
		char strBuffer[MAXBUF];

		CreateSavedFilePath();

		HANDLE hFile = ::CreateFile(m_strSavedFilePath,
										GENERIC_WRITE,
										0,
										NULL,
										CREATE_ALWAYS,
										FILE_ATTRIBUTE_NORMAL,
										NULL);
		if (INVALID_HANDLE_VALUE == hFile) {
			return false;
		}
		UINT uiCount;
		DWORD dwBytesWritten = 0;
		do {
			uiCount = m_pHttpFile->Read(strBuffer, MAXBUF);
			if (uiCount != 0) {
				::WriteFile(hFile, strBuffer, uiCount, &dwBytesWritten, NULL);
			}
		} while (uiCount != 0);
		::CloseHandle(hFile);

		return true;
	}

	return false;
}

CHttpDownloader::CHttpDownloader () : m_nPort(80) {
	
	ZeroMemory(m_strURL, MAX_URL_LENGTH);
	ZeroMemory(m_strFileName, MAX_FILE_NAME);
	ZeroMemory(m_strSavingFolderPath, MAX_PATH);
	ZeroMemory(m_strSavedFilePath, MAX_PATH);

	m_pHttpConnection = NULL;
	m_pHttpFile = NULL;
}

bool CHttpDownloader::SetURL(const TCHAR* strURL) {

	CString cstrURL = strURL;
	cstrURL.Replace(_T("http://"), _T(""));
	cstrURL.Replace(_T("https://"), _T(""));
	cstrURL.Remove(L'/');

	if (0 == lstrcmpi(cstrURL.GetBuffer(), m_strURL)) {
		return false;
	}
	_tcscpy_s(m_strURL, MAX_URL_LENGTH, cstrURL.GetBuffer());

	CleanUp();
	m_pHttpConnection = m_internetSession.GetHttpConnection(m_strURL, m_nPort); //throw CInternetException

	return TRUE;
}

bool CHttpDownloader::SetFileName(const TCHAR* strFileName) {

	CString cstrFileName = strFileName;
	cstrFileName.Replace(L'\\', L'/');

	_tcscpy_s(m_strFileName, MAX_FILE_NAME, cstrFileName.GetBuffer());
	
	return TRUE;
}

bool CHttpDownloader::SetSavingFolderPath(const TCHAR* strSavingFolderPath) {

	_tcscpy_s(m_strSavingFolderPath, MAX_PATH, strSavingFolderPath);

	if (L'\\' == m_strSavingFolderPath[lstrlen(m_strSavingFolderPath) - 1]) {
		 m_strSavingFolderPath[lstrlen(m_strSavingFolderPath) - 1] = L'\0';
	}
	return TRUE;
}

void CHttpDownloader::CreateSavedFilePath() {

	CString cstrFileName = m_strFileName;

	int iFoundIndex = cstrFileName.ReverseFind(L'/');
	if (iFoundIndex >= 0) {
		cstrFileName = cstrFileName.Right(cstrFileName.GetLength() - iFoundIndex - 1);
	}

	CString cstrSavedFilePath;
	
	cstrSavedFilePath.Format(_T("%s\\%s"), m_strSavingFolderPath, cstrFileName.GetBuffer());
	_tcscpy_s(m_strSavedFilePath, MAX_PATH, cstrSavedFilePath.GetBuffer());
}