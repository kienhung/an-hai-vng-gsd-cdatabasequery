#pragma once

class CWinTabBrowser
{
private:
	CString m_strTitle;
	CString m_strURL;
public:
	CWinTabBrowser(BSTR strTtile, BSTR strURL);
	CWinTabBrowser(CString pstrTitle, CString pstrURL);
	~CWinTabBrowser(void);

	BOOL CompareWinTab(const CWinTabBrowser* winTab);
	BOOL CompareServerHost(const TCHAR* pstrURL);

	CString GetServerHost(const TCHAR* pstrURL);
	CString GetServerHostAndPath(const TCHAR* pstrURL);

	CString GetTitle();
	CString GetURL();
};
