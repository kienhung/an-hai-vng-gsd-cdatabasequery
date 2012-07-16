#pragma once
#include <afxinet.h>

#define MAX_URL_LENGTH 256
#define MAX_FILE_NAME 50

class AFX_EXT_CLASS CHttpDownloader
{
protected:


	TCHAR m_strURL[MAX_URL_LENGTH];
	TCHAR m_strFileName[MAX_FILE_NAME];

	TCHAR m_strSavingFolderPath[MAX_PATH];
	TCHAR m_strSavedFilePath[MAX_PATH];

	CInternetSession m_internetSession;
	CHttpConnection* m_pHttpConnection;
	CHttpFile* m_pHttpFile;

	const INTERNET_PORT m_nPort;

	void CleanUp();
	void CreateSavedFilePath();
public:
	CHttpDownloader();
	bool DownLoad();

	bool SetURL(const TCHAR* strURL);
	bool SetFileName(const TCHAR* strFileName);
	bool SetSavingFolderPath(const TCHAR* strSavingFolderPath);

	virtual ~CHttpDownloader(void);
};
