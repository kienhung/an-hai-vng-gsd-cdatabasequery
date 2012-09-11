#pragma once
#include "StdAfx.h"
#include "BlackListDAO.h"
#include "StringConverter.h"
CBlackListDAO::CBlackListDAO()
{
	
}

CBlackListDAO::~CBlackListDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CBlackListDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}
BOOL CBlackListDAO::AddBlackWeb(const BLACKLIST& blackList)
{
	if(CheckBlackExist(blackList.strURL))
	{
		return TRUE;
	}

	char strURL[MAX_PATH] = {0};
	char strRecordDate[MAX_STRINGDATE*2 + 1] = {0};

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(blackList.strURL);
	if(NULL != pcBuffer)
		strcpy_s(strURL, MAX_PATH, pcBuffer);
	
	pcBuffer = stringConverter.UnicodeToUTF8(blackList.strRecordDate);
	if(NULL != pcBuffer)
		strcpy_s(strRecordDate, MAX_STRINGDATE*2 + 1, pcBuffer);
	if(strlen(strRecordDate) == 0)
	{
		SYSTEMTIME Time;
		::GetLocalTime(&Time);

		CStringA cstrTime;
		cstrTime.Format("%u-%u-%u %u:%u:%u", Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond);
		sprintf_s(strRecordDate, cstrTime);
	}
	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO blacklisttb (URL,RecordDate) VALUES ('%s', '%s')",strURL, strRecordDate);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

BOOL CBlackListDAO::AddBlackWeb(const TCHAR* strOutURL)
{
	if(CheckBlackExist(strOutURL))
	{
		return TRUE;
	}
	BLACKLIST blackList(strOutURL);
	char strURL[MAX_PATH] = {0};
	char strRecordDate[MAX_STRINGDATE*2 + 1] = {0};

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(blackList.strURL);
	if(NULL != pcBuffer)
		strcpy_s(strURL, MAX_PATH, pcBuffer);

	pcBuffer = stringConverter.UnicodeToUTF8(blackList.strRecordDate);
	if(NULL != pcBuffer)
		strcpy_s(strRecordDate, MAX_STRINGDATE*2 + 1, pcBuffer);
	if(strlen(strRecordDate) == 0)
	{
		SYSTEMTIME Time;
		::GetLocalTime(&Time);

		CStringA cstrTime;
		cstrTime.Format("%u-%u-%u %u:%u:%u", Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond);
		sprintf_s(strRecordDate, cstrTime);
	}
	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO blacklisttb (URL,RecordDate) VALUES ('%s', '%s')",strURL, strRecordDate);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

BOOL CBlackListDAO::CheckBlackExist( const TCHAR * strURL )
{
	CStringConverter stringConverter;
	
	char *pcBuffer = stringConverter.UnicodeToUTF8(strURL);
	if(NULL == pcBuffer)
		return FALSE;

	CStringA cstrSelectQuery;
	cstrSelectQuery.Format("SELECT count(URL) FROM blacklisttb WHERE URL = '%s';", pcBuffer);
	MYSQL_RES *pMySQLQueryResult =  m_pSQLDataAccessHelper->ExecuteQuery(cstrSelectQuery);

	if(NULL == pMySQLQueryResult)
	{
		return FALSE;
	}
	MYSQL_ROW mySQLResultRow;
	if((mySQLResultRow = mysql_fetch_row(pMySQLQueryResult)))
	{
		int iCount = atoi(mySQLResultRow[0]);
		if(iCount > 0)
		{
			m_pSQLDataAccessHelper->FreeQueryResult(pMySQLQueryResult);
			return TRUE;
		}
	}
	m_pSQLDataAccessHelper->FreeQueryResult(pMySQLQueryResult);
	return FALSE;
}

BOOL CBlackListDAO::UpdateAddedBy( LPCTSTR strUrl, int iNewAddedBy, int iWhereAddedBy )
{
	CStringConverter stringConverter;
	char *strUTF8Url = stringConverter.UnicodeToUTF8(strUrl);

	CStringA strSql;
	strSql.Format("update ddm.blacklisttb set addedBy = %d where URL like '%s' and AddedBy = %d", iNewAddedBy, strUTF8Url, iWhereAddedBy);

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

BOOL CBlackListDAO::RemoveInvalidURL()
{
	CStringA strSql;
	strSql.Format("DELETE FROM blacklisttb WHERE AddedBy = 0");

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

//::OutputDebugStringA(strSql);
//::OutputDebugStringA("\n");