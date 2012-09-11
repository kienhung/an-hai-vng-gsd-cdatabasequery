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
		iActive = 1;
		iAddedBy = 1;
	}
	BLACKLIST(const TCHAR* strOutURL)
	{
		wmemset(strURL, 0, MAX_PATH);
		wmemset(strRecordDate, 0, MAX_STRINGDATE);
		swprintf(strURL, MAX_PATH, strOutURL);
		iActive = 1;
		iAddedBy = 1;
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
	BOOL AddBlackWeb(const TCHAR* strURL);
	BOOL CheckBlackExist(const TCHAR * strURL);
	BOOL UpdateAddedBy(LPCTSTR strUrl, int iNewAddedBy, int iWhereAddedBy);
	BOOL RemoveInvalidURL();

	~CBlackListDAO(void);
};
