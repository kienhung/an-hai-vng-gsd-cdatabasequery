#pragma once

#define MAX_STRINGDATE 20
#define MAX_NAME 100
#define MAX_USERNAME 25
#define MAX_ADDRESS 150
#define MAX_PHONE 15
#define MAX_EMAIL 50
#define MAX_INTTIME 12
#define MAX_SERVICENAME 50
#define MAX_MONEY 15
#define MAX_LENGTH 50

typedef struct	
{
	bool m_bIsConnected;
	char m_strUsername[MAX_LENGTH];
	char m_strPasssword[MAX_LENGTH];
	char m_strServerAddress[MAX_LENGTH];
	char m_strDatabaseName[MAX_LENGTH];
}CONNECTSTRINGTOMYSQL;

typedef struct	
{
	TCHAR strURL[MAX_PATH];
	TCHAR strRecordDate[MAX_STRINGDATE];
	int iActive;
	int iAddedBy;
}BLACKLIST;

struct CSM_SERVICE	
{
	TCHAR strServiceName[MAX_SERVICENAME];
	TCHAR strUnit[MAX_LENGTH];
	int iServicePrice;

	CSM_SERVICE()
	{
		wmemset(strServiceName, 0, MAX_SERVICENAME);
		wmemset(strUnit, 0, MAX_LENGTH);
	}
};


struct	CSM_USER
{
	TCHAR strName[MAX_NAME] ;
	TCHAR strBirthDay[MAX_STRINGDATE];
	TCHAR strUsername[MAX_USERNAME];
	TCHAR strUserType[3];
	TCHAR strRecordDate[MAX_STRINGDATE];
	TCHAR strExpiryDate[MAX_STRINGDATE];
	TCHAR strAddress[MAX_ADDRESS];
	TCHAR strPhone[MAX_PHONE];
	TCHAR strEmail[MAX_EMAIL];
	TCHAR strRemainTime[MAX_INTTIME];
	TCHAR strTimeUsed[MAX_INTTIME];
	TCHAR strFreeTime[MAX_INTTIME];
	TCHAR strRemainMoney[MAX_MONEY];
	TCHAR strFreeMoney[MAX_MONEY];
	TCHAR strActive[3];
	
	CSM_USER()
	{
		wmemset(strName, 0, MAX_NAME);
		wmemset(strBirthDay, 0, MAX_STRINGDATE);
		wmemset(strUsername, 0, MAX_USERNAME);
		wmemset(strUserType, 0, 3);
		wmemset(strRecordDate, 0, MAX_STRINGDATE);
		wmemset(strExpiryDate, 0, MAX_STRINGDATE);
		wmemset(strAddress, 0, MAX_ADDRESS);
		wmemset(strPhone, 0, MAX_PHONE);
		wmemset(strEmail, 0, MAX_EMAIL);
		wmemset(strRemainTime, 0, MAX_INTTIME);
		wmemset(strTimeUsed, 0, MAX_INTTIME);
		wmemset(strFreeTime, 0, MAX_INTTIME);
		wmemset(strRemainMoney, 0, MAX_MONEY);
		wmemset(strFreeMoney, 0, MAX_MONEY);
		wmemset(strActive, 0, 3);
	};
};


typedef struct	
{
	
}CSM_PRICEMACHINE;