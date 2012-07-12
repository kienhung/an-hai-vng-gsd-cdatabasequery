#pragma once

class CMySQLDataAccessHelper
{
private:
	MYSQL *m_mySQLConnection;

public:
	CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	MYSQL_RES* ExecuteQuery(const char *strQuery);
	void ExecuteNonQuery(const char *strQuery);
	void FreeQueryResult(MYSQL_RES *pMySQLQueryResult);
	static bool CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	~CMySQLDataAccessHelper(void);
};
