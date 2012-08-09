#pragma once
#include "MyStruct.h"
#include "MySQLDataAccessHelper.h"


class CServiceDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
public:
	CServiceDAO(void);
	~CServiceDAO(void);

	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddService(const CSM_SERVICE &csm_Service);
};
