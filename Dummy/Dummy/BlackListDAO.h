#pragma once

#include <list>
#include "MySQLDataAccessHelper.h"
using namespace std;
#define MAX_STRINGDATE 20

struct	BLACKLIST
{
	TCHAR strURL[MAX_PATH];
	TCHAR strRecordDate[MAX_STRINGDATE];
	int iActive;
	int iAddedBy;
	BLACKLIST()
	{
		wmemset(strURL, 0, MAX_PATH);
		wmemset(strRecordDate, 0, MAX_STRINGDATE);
		
	}
};

class CBlackListDAO
{
private:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;

public:
	CBlackListDAO(void);
	BOOL ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	BOOL AddBlackWeb(const BLACKLIST &blackList);
	BOOL CheckBlackExist(const TCHAR * strURL);
	~CBlackListDAO(void);
};
