#pragma once

#define MAX_STRINGDATE 15
typedef struct	
{
	TCHAR strURL[MAX_PATH];

	TCHAR strRecordDate[MAX_STRINGDATE];
	int iActive;
	int iAddedBy;
}BACKLIST;