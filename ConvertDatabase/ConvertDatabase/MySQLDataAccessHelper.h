#pragma once
#include "StdAfx.h"

class CMySQLDataAccessHelper
{
private:
	MYSQL *m_mySQLConnection;
	BOOL m_bIsConnected;
public:
	CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	BOOL IsConnected();
	MYSQL_RES* ExecuteQuery(const char *strQuery);
	BOOL ExecuteNonQuery(const char *strQuery);
	void FreeQueryResult(MYSQL_RES *pMySQLQueryResult);
	static bool CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	~CMySQLDataAccessHelper(void);
};
