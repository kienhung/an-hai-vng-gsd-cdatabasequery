#pragma once
#include "MyStruct.h"
#include <list>
#include "MySQLDataAccessHelper.h"
using namespace std;

class CBackListDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

public:
	CBackListDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddBackList(const BACKLIST &backList);
	~CBackListDAO(void);
};
