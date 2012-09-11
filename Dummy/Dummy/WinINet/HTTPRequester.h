#pragma once


class CHTTPRequester
{

protected:

	HINTERNET m_hSession;
	HINTERNET m_hConnection;
	HINTERNET m_hRequest;

	CString m_strHeader;

public:

	CHTTPRequester(void);
	~CHTTPRequester(void);

	BOOL PostRequest(LPCTSTR strServer, LPCTSTR strObjectName, LPVOID buffer, size_t uiBufferSize);
	BOOL PostRequest(LPCTSTR strServer, LPCTSTR strObjectName, LPCTSTR strData);
	BOOL PostRequest(LPCTSTR strURL, LPCTSTR strData);
protected:

	void Initalize();
	void CleanUp();
};
