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

BOOL CBlackListDAO::UpdateAddedBy( const char* strUrl, int iNewAddedBy, int iWhereAddedBy )
{
	CStringA strSql;
	strSql.Format("update ddm.blacklisttb set addedBy = %d where URL like '%s' and AddedBy = %d", iNewAddedBy, strUrl, iWhereAddedBy);

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

BOOL CBlackListDAO::RemoveInvalidURL()
{
	CStringA strSql;
	strSql.Format("DELETE FROM blacklisttb WHERE AddedBy = 0");

	return m_pSQLDataAccessHelper->ExecuteNonQuery(strSql);
}

BOOL CBlackListDAO::CheckURLExist( const char *strURL )
{
	CStringA cstrSelectQuery;
	cstrSelectQuery.Format("SELECT count(URL) FROM blacklisttb WHERE URL = '%s';", strURL);

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
	cstrQuery.Format("INSERT INTO blacklisttb (URL, Title, Description, RecordDate) VALUES ('%s', '', '', '%s')", strURL, cstrRecordDate);
	
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

