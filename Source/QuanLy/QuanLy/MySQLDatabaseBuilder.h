#pragma once
#include "MySQLdataaccesshelper.h"

class CMySQLDatabaseBuilder
{
protected:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

	const char *m_strUser;
	const char *m_strPassword;
	const char *m_strServerAddress;
	const char *m_strDatabase;
	
	unsigned int m_uiPort;
public:
	CMySQLDatabaseBuilder(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort = 0);
	void Build();
	virtual ~CMySQLDatabaseBuilder(void);
};
