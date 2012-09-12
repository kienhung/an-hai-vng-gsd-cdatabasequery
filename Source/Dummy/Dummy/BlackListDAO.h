#pragma once

#include "MySQLDataAccessHelper.h"

class CBlackListDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

public:
	CBlackListDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);

	BOOL InsertURL(const char *strURL);
	BOOL CheckURLExist(const char *strURL);
	BOOL UpdateAddedBy(const char* strUrl, int iNewAddedBy, int iWhereAddedBy);
	BOOL RemoveInvalidURL();

	~CBlackListDAO(void);
};
