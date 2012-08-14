#pragma once
#include "StdAfx.h"
#include "BlackListDAO.h"
#include "StringConverter.h"
CBlackListDAO::CBlackListDAO()
{
	
}

CBlackListDAO::~CBlackListDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CBlackListDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}
BOOL CBlackListDAO::AddBlackList(const BLACKLIST& blackList)
{
	char strURL[MAX_PATH] = {0};
	char strRecordDate[MAX_STRINGDATE*2 + 1] = {0};

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(blackList.strURL);
	if(NULL != pcBuffer)
		strcpy_s(strURL, MAX_PATH, pcBuffer);
	
	pcBuffer = stringConverter.UnicodeToUTF8(blackList.strRecordDate);
	if(NULL != pcBuffer)
		strcpy_s(strRecordDate, MAX_STRINGDATE*2 + 1, pcBuffer);

	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO blacklisttb (URL,RecordDate,Active,AddedBy) VALUES ('%s', '%s', %d, %d)",strURL, strRecordDate, blackList.iActive, blackList.iAddedBy);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

