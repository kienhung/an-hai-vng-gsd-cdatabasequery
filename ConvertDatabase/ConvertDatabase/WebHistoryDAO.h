#pragma once
#include "MyStruct.h"
#include "MySQLDataAccessHelper.h"

class CWebHistoryDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
public:
	CWebHistoryDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddHistory(const CSM_WEBHISTORY &webHistory);
	~CWebHistoryDAO(void);
};
