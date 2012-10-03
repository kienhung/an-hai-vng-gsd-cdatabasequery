#pragma once

#include "MySQLDataAccessHelper.h"

class CBlackListDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
	const static int INFO_SOFT_ADDED_BY = 3;

public:
	CBlackListDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);

	BOOL InsertURL(const char *strURL);
	BOOL CheckURLExist(const char *strURL);

	BOOL UpdateActive(const char *strUrl, int iNewActive);
	BOOL RemoveInactiveURL();

	~CBlackListDAO(void);
};
