#include "StdAfx.h"
#include "WebHistoryDAO.h"
#include "StringConverter.h"

CWebHistoryDAO::CWebHistoryDAO(void)
{
}

CWebHistoryDAO::~CWebHistoryDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CWebHistoryDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}

BOOL CWebHistoryDAO::AddHistory(const CSM_WEBHISTORY &webHistory)
{
	char strURL[MAX_PATH] = {0};
	char strRecordDate[MAX_STRINGDATE*2 + 1] = {0};
	char strMachine[MAX_NAME* 2 +1] = {0};

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(webHistory.strURL);
	if(NULL != pcBuffer)
		strcpy_s(strURL, MAX_PATH, pcBuffer);
	
	pcBuffer = stringConverter.UnicodeToUTF8(webHistory.strRecordDate);
	if(NULL != pcBuffer)
		strcpy_s(strRecordDate, MAX_STRINGDATE*2 + 1, pcBuffer);

	pcBuffer = stringConverter.UnicodeToUTF8(webHistory.strMachine);
	if(NULL != pcBuffer)
		strcpy_s(strMachine, MAX_NAME*2 + 1, pcBuffer);
	
	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO webhistorytb (URL,RecordDate,UserId,Machine) VALUES ('%s', '%s', %d, '%s')",strURL, strRecordDate, webHistory.iUserId, strMachine);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}
