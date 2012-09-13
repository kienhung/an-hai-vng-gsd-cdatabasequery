#pragma once
#include "MySQLDataAccessHelper.h"

class CIntOptionDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
public:
	CIntOptionDAO(void);
	~CIntOptionDAO(void);

	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);

	CString GetLicesenID();
};
