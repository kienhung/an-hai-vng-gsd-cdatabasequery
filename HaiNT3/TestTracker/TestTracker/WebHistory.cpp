#include "StdAfx.h"
#include "WebHistory.h"
#include "define.h"
#include "MyUtils.h"

//#pragma comment(lib, "SQLite/qlite3.lib")
#pragma comment(lib, "SQLite/LibSqlite3.lib")


CWebHistory::CWebHistory(void)
{
	m_bBrowserType = 0;
	m_bInit = FALSE;
	memset(m_strHistoryPath, 0, sizeof(m_strHistoryPath));
	memset(m_strHistoryTempPath, 0, sizeof(m_strHistoryTempPath));
}

CWebHistory::~CWebHistory(void)
{
}

BOOL CWebHistory::Initialize(BYTE iBrowserType)
{
	m_bBrowserType = iBrowserType;

	if (iBrowserType == FIREFOX_BROWSER)
	{
		m_strSelectName = _T("moz_places.url");
		m_strHistoryTable = _T("moz_historyvisits");
		m_strWebAddressTable = _T("moz_places");
		m_strHistoryTableWebID = _T("moz_historyvisits.place_id");
		m_strHistoryTableID = _T("moz_historyvisits.id");
		m_strWebAddressTableID = _T("moz_places.id");
		m_strLastID = _T("0");

		TCHAR strPath[MAX_PATH] = {0};

		if (CMyUtils::GetSpecialFolder(CSIDL_APPDATA, strPath))
		{
			CFileFind finder;

			_tcscpy(strPath + _tcslen(strPath), _T("\\Mozilla\\Firefox\\Profiles\\*.default"));
			if (finder.FindFile(strPath))
			{
				finder.FindNextFile();
				_stprintf(m_strHistoryPath, _T("%s\\places.sqlite"), finder.GetFilePath());
				finder.Close();

				if (GetTempPath(MAX_PATH, strPath))
				{
					_stprintf(m_strHistoryTempPath, _T("%s\\FirefoxHistoryTemp.db"), strPath);
					m_bInit = TRUE;
				}
			}
		}
	}
	else if ( iBrowserType == CHROME_BROWSER)
	{
		m_strSelectName = _T("urls.url");
		m_strHistoryTable = _T("visits");
		m_strWebAddressTable = _T("urls");
		m_strHistoryTableWebID = _T("visits.url");
		m_strHistoryTableID = _T("visits.id");
		m_strWebAddressTableID = _T("urls.id");
		m_strLastID = _T("0");

		TCHAR strPath[MAX_PATH] = {0};

		if (CMyUtils::GetSpecialFolder(CSIDL_LOCAL_APPDATA, strPath))
		{
			_stprintf(m_strHistoryPath, _T("%s\\Google\\Chrome\\User Data\\Default\\History"), strPath);

			if (GetTempPath(MAX_PATH, strPath))
			{
				_stprintf(m_strHistoryTempPath, _T("%s\\ChromeHistoryTemp.db"), strPath);
				m_bInit = TRUE;
			}
		}
	}

	if (m_bInit)
		m_bInit = GetLastID();

	return m_bInit;
}

BOOL CWebHistory::GetLastID()
{
	BOOL bRet = FALSE;

	if (CMyUtils::CopyFile(m_strHistoryPath, m_strHistoryTempPath, FALSE))
	{
		if (db.Open(m_strHistoryTempPath) == SQLITE_OK)
		{
			if (db.BeginTransaction())
			{
				CString strQuery;
				strQuery.Format(_T("SELECT %s FROM %s ORDER BY %s DESC LIMIT 1"), m_strHistoryTableID, m_strHistoryTable, m_strHistoryTableID);
				SQLite::TablePtr table = db.QuerySQL2(strQuery);
				bRet = (db.GetLastError() == SQLITE_OK);
				db.CommitTransaction();
				if (bRet)
				{
					if (table.m_pTable->GetRowCount() > 0)
						m_strLastID = table.m_pTable->GetValue(0);
				}
				table.Destroy();
			}
			db.Close();
		}
		DeleteFile(m_strHistoryTempPath);
	}

	return bRet;
}

void CWebHistory::UpdateURL()
{
	if (!m_bInit)
	{
		m_bInit = Initialize(m_bBrowserType);
		return;
	}

	if (CMyUtils::CopyFile(m_strHistoryPath, m_strHistoryTempPath, FALSE))
	{
		if (db.Open(m_strHistoryTempPath) == SQLITE_OK)
		{
			if (db.BeginTransaction())
			{
				CString strQuery,
						strPreURL;
				LPCTSTR strURL;
				int		iRowCount,
						i = 0;

				strQuery.Format(_T("SELECT %s, %s FROM %s, %s WHERE %s = %s AND %s > %s ORDER BY %s ASC"), m_strHistoryTableID, m_strSelectName, m_strHistoryTable, m_strWebAddressTable, m_strHistoryTableWebID, m_strWebAddressTableID, m_strHistoryTableID, m_strLastID, m_strHistoryTableID);
				SQLite::TablePtr table = db.QuerySQL2(strQuery);
				db.CommitTransaction();
				
				iRowCount = table.m_pTable->GetRowCount();
				while (i < iRowCount)
				{
					m_strLastID = table.m_pTable->GetValue(0);
					strURL = table.m_pTable->GetValue(1);
					if (strPreURL.CompareNoCase(strURL) != 0)
					{
						////////
					}
					strPreURL = strURL;
					table.m_pTable->GoNext();
					++i;
				} 
				table.Destroy();
				db.Close();
			}
		}
		DeleteFile(m_strHistoryTempPath);
	}
}
