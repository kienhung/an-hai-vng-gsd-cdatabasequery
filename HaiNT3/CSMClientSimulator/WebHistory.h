#pragma once
#include "SQLite/SQLite.h"

#define FIREFOX_BROWSER		1
#define CHROME_BROWSER		2

class CWebHistory
{
private:
	BYTE	m_bBrowserType;
	BOOL	m_bInit;
	BOOL	m_bOldVersionChrome;
	TCHAR m_strHistoryPath[MAX_PATH];
	TCHAR m_strHistoryTempPath[MAX_PATH];
	CString m_strLastID;
	
	CString m_strSelectName;
	CString m_strSelectDatetime;
	CString m_strHistoryTable;
	CString m_strWebAddressTable;
	CString m_strHistoryTableWebID;
	CString m_strHistoryTableID;
	CString m_strWebAddressTableID;
	
	SQLite::Database db;

	BOOL GetLastID();
public:
	CWebHistory(void);
	~CWebHistory(void);

	BOOL Initialize(BYTE iBrowserType);
	BOOL InitializeForFirefox();
	BOOL InitializeForChrome(const BOOL& bOldVersion = FALSE);
	void UpdateURL();

};
