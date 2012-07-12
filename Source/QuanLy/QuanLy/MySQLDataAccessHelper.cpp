#include "StdAfx.h"
#include "MySQLDataAccessHelper.h"
#include "MyException.h"
/*
CMySQLDataAccessHelper::CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort)
{
	m_mySQLConnection = mysql_init(NULL);
	if (NULL == m_mySQLConnection) {
		throw new CMyException("Failure to initialize the MYSQL object", MY_SQL);
	}

	if (NULL == mysql_real_connect(m_mySQLConnection, strServerAddress, strUser, strPassword, strDatabase, uiPort, NULL, 0)) {
		throw new CMyException("Failure to connect database", MY_SQL);
	}
}

CMySQLDataAccessHelper::~CMySQLDataAccessHelper(void)
{
	if (NULL != m_mySQLConnection) {
		mysql_close(m_mySQLConnection);
	}
}

MYSQL_RES* CMySQLDataAccessHelper::ExecuteQuery(const char *strQuery) {

	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		throw new CMyException("Failure to execute query", MY_SQL);
	}
	
	MYSQL_RES *pMySQLQueryResult = mysql_store_result(m_mySQLConnection);
	if (NULL == pMySQLQueryResult) {
		throw new CMyException("Failure to get results of the query", MY_SQL);
	}
	return pMySQLQueryResult;
}

void CMySQLDataAccessHelper::FreeQueryResult(MYSQL_RES *pMySQLQueryResult) {
	mysql_free_result(pMySQLQueryResult);
}

void CMySQLDataAccessHelper::ExecuteNonQuery(const char *strQuery) {
	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		throw new CMyException("Failure to execute query", MY_SQL);
	}
}
*/
bool CMySQLDataAccessHelper::CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort) {

	return true;
}