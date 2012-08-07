#pragma once
#include "MyStruct.h"
#include <list>
#include "MySQLDataAccessHelper.h"
using namespace std;

class CUserDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

public:
	CUserDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddUser(const CSM_USER &csm_User);
	INT GetMoneyFromTime(const int& iTime, const int& iUserType);
	INT GetUnitPriceFromUserType(const int& iUserType);
	~CUserDAO(void);
};
