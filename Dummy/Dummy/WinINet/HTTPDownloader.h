#pragma once

class CHTTPDownloader
{
protected:

	HANDLE			m_hFile;
	HINTERNET		m_hSession;
	HINTERNET		m_hConnection;

public:

	CHTTPDownloader(void);
	~CHTTPDownloader(void);

	BOOL Download(LPCTSTR strURL, LPCTSTR strFilePath);

protected:

	void CleanUp();
	BOOL SaveFile(LPCTSTR strFilePath);
};
