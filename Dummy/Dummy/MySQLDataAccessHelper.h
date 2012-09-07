#pragma once
#include "StdAfx.h"
#include <mysql.h>
#include <afxdhtml.h>
#pragma comment(lib, "libmysql")

class CMySQLDataAccessHelper
{
private:
	MYSQL *m_mySQLConnection;
	BOOL m_bIsConnected;
	char* m_strPass;
public:
	CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	BOOL IsConnected();
	VOID Disconnect();
	MYSQL_RES* ExecuteQuery(const char *strQuery);
	BOOL ExecuteNonQuery(const char *strQuery);
	void FreeQueryResult(MYSQL_RES *pMySQLQueryResult);
	static bool CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	~CMySQLDataAccessHelper(void);

	VOID GetPassWordMySQL();
	char* GetPassWord();
	VOID DeCodeString(const CString &strIN, CString & strOUT);
};
