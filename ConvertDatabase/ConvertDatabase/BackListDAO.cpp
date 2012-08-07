#pragma once
#include "StdAfx.h"
#include "BackListDAO.h"
#include "StringConverter.h"
CBackListDAO::CBackListDAO()
{
	
}

CBackListDAO::~CBackListDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CBackListDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}
BOOL CBackListDAO::AddBackList(const BACKLIST& backList)
{
	char strURL[MAX_PATH];
	char strRecordDate[MAX_STRINGDATE*2 + 1];

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(backList.strURL);
	strcpy_s(strURL, MAX_PATH, pcBuffer);
	
	pcBuffer = stringConverter.UnicodeToUTF8(backList.strRecordDate);
	strcpy_s(strRecordDate, MAX_STRINGDATE*2 + 1, pcBuffer);

	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO blacklisttb (URL,RecordDate,Active,AddedBy) VALUES ('%s', '%s', %d, %d)",strURL, strRecordDate, backList.iActive, backList.iAddedBy);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}

