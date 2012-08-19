#pragma once
#include "StdAfx.h"
#include "MySQLDataAccessHelper.h"

CMySQLDataAccessHelper::CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort)
{
	m_mySQLConnection = mysql_init(NULL);
	if (NULL == m_mySQLConnection) {
		m_bIsConnected = FALSE;
		return;
	}
	
	if (mysql_options(m_mySQLConnection, MYSQL_SET_CHARSET_NAME, "utf8"))
	{
		m_bIsConnected = FALSE;
		return;
	}

	if (NULL == mysql_real_connect(m_mySQLConnection, strServerAddress, strUser, strPassword, strDatabase, uiPort, NULL, 0)) {
		m_bIsConnected = FALSE;
		return;
	}
	m_bIsConnected = TRUE;
}

CMySQLDataAccessHelper::~CMySQLDataAccessHelper(void)
{
	if (NULL != m_mySQLConnection) {
		mysql_close(m_mySQLConnection);
	}
}

VOID CMySQLDataAccessHelper::Disconnect()
{
	if (NULL != m_mySQLConnection) {
		mysql_close(m_mySQLConnection);
	}
}

BOOL CMySQLDataAccessHelper::IsConnected()
{
	return m_bIsConnected;
}

MYSQL_RES* CMySQLDataAccessHelper::ExecuteQuery(const char *strQuery) {

	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		
		//throw new CMyException("Failure to execute query", MY_SQL);
		AfxMessageBox(_T("Failure to execute query"), MB_ICONSTOP, 0);
		return NULL;
	}
	
	MYSQL_RES *pMySQLQueryResult = mysql_store_result(m_mySQLConnection);
	if (NULL == pMySQLQueryResult) {
		//throw new CMyException("Failure to get results of the query", MY_SQL);
		AfxMessageBox(_T("Failure to get results of the query"), MB_ICONSTOP, 0);
		return NULL;
	}
	return pMySQLQueryResult;
}


void CMySQLDataAccessHelper::FreeQueryResult(MYSQL_RES *pMySQLQueryResult) {
	mysql_free_result(pMySQLQueryResult);
	
}

BOOL CMySQLDataAccessHelper::ExecuteNonQuery(const char *strQuery) {
	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		//throw new CMyException("Failure to execute query", MY_SQL);
		//AfxMessageBox(_T("Failure to execute query"), MB_ICONSTOP, 0);
		return FALSE;
	}
	return TRUE;
}

bool CMySQLDataAccessHelper::CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort) {

	MYSQL *mySQLConnection = mysql_init(NULL);
	if (NULL == mySQLConnection) {
		return false;
	}
	bool bFresult = true;
	if (NULL ==	mysql_real_connect(mySQLConnection, strServerAddress, strUser, strPassword, NULL, uiPort, NULL, 0)) {
		bFresult = false;
	}
	mysql_close(mySQLConnection);
	return bFresult;
}