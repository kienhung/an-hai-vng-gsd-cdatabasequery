#pragma once
#include "MyStruct.h"
#include <list>
#include "MySQLDataAccessHelper.h"
using namespace std;

class CBlackListDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

public:
	CBlackListDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddBackList(const BLACKLIST &blackList);
	~CBlackListDAO(void);
};
