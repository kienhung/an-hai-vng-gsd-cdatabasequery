#pragma once
#include "StdAfx.h"
#include "ServiceDAO.h"
#include "StringConverter.h"
CServiceDAO::CServiceDAO(void)
{
}

CServiceDAO::~CServiceDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CServiceDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}

BOOL CServiceDAO::AddService(const CSM_SERVICE &csm_Service)
{
	
	char strServiceName[(MAX_SERVICENAME +1)*2] = {0};
	char strUnit[(MAX_LENGTH +1)*2] = {0};
	

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(csm_Service.strServiceName);
	if(NULL != pcBuffer)
		strcpy_s(strServiceName, (MAX_SERVICENAME +1)*2, pcBuffer);

	pcBuffer = stringConverter.UnicodeToUTF8(csm_Service.strUnit);
	if(NULL != pcBuffer)
		strcpy_s(strUnit, (MAX_LENGTH +1)*2, pcBuffer);

	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO servicetb (ServiceName,ServicePrice,Unit) VALUES (N'%s', '%d', N'%s')",strServiceName, csm_Service.iServicePrice, strUnit);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}