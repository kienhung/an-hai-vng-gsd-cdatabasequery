#pragma once
#include "MyStruct.h"
#include <list>
#include "MySQLDataAccessHelper.h"
#include "resource.h"
using namespace std;

class CUserDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
	
public:
	static bool  m_bUpdateUser;
	CUserDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddUser(const CSM_USER &csm_User);
	INT GetMoneyFromTime(const int& iTime, const int& iUserType);
	INT GetUnitPriceFromUserType(const int& iUserType);
	~CUserDAO(void);
	BOOL DeleteUser(const char* strUserName);
};

