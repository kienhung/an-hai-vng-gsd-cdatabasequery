#pragma once
#include "StdAfx.h"
#include "BlackListDAO.h"


CBlackListDAO::CBlackListDAO()
{
	m_pSQLDataAccessHelper = NULL;
}

CBlackListDAO::~CBlackListDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL)
	{
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CBlackListDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	if (m_pSQLDataAccessHelper != NULL)
	{
		delete m_pSQLDataAccessHelper;
	}
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}



BOOL CBlackListDAO::CheckURLExist( const char *strURL )
{
	CStringA cstrSelectQuery;

	cstrSelectQuery.Format("SELECT count(URL) FROM blacklisttb 	WHERE URL like '%s' and (addedBy = 3 or (addedBy != 3 and Active = 1))", strURL);

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

BOOL CBlackListDAO::InsertURL( const char *strURL )
{
	SYSTEMTIME Time;
	::GetLocalTime(&Time);

	CStringA cstrRecordDate;
	cstrRecordDate.Format("%u-%u-%u %u:%u:%u", Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond);

	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO blacklisttb (URL, Title, Description, RecordDate, AddedBy) VALUES ('%s', '', '', '%s', 3)", strURL, cstrRecordDate);
	
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

BOOL CBlackListDAO::UpdateActive( const char *strUrl, int iNewActive )
{
	CStringA strSql;
	strSql.Format("UPDATE blacklisttb SET Active = %d WHERE URL like '%s' and AddedBy = %d ", iNewActive, strUrl, INFO_SOFT_ADDED_BY);

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

BOOL CBlackListDAO::RemoveInactiveURL()
{
	CStringA strSql;
	strSql.Format("DELETE FROM blacklisttb WHERE AddedBy = %d and Active = 0", INFO_SOFT_ADDED_BY);

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

