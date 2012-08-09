#pragma once

#define MAX_STRINGDATE 15
#define MAX_NAME 15
#define MAX_USERNAME 25
#define MAX_ADDRESS 150
#define MAX_PHONE 15
#define MAX_EMAIL 50
#define MAX_INTTIME 12
#define MAX_SERVICENAME 25

typedef struct	
{
	TCHAR strURL[MAX_PATH];
	TCHAR strRecordDate[MAX_STRINGDATE];
	int iActive;
	int iAddedBy;
}BLACKLIST;

typedef struct	
{
	TCHAR strServiceName[MAX_SERVICENAME];
	int iServicePrice;
}CSM_SERVICE;


typedef struct	
{
	TCHAR strName[MAX_NAME];
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
}CSM_USER;

