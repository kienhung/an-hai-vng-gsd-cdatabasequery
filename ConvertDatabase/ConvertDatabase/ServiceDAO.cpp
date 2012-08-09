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
	
	char strServiceName[MAX_PATH];
	

	CStringConverter stringConverter;

	char *pcBuffer = stringConverter.UnicodeToUTF8(csm_Service.strServiceName);
	strcpy_s(strServiceName, MAX_PATH, pcBuffer);

	CStringA cstrQuery;
	cstrQuery.Format("INSERT INTO servicetb (ServiceName,ServicePrice) VALUES (N'%s', '%d')",strServiceName, csm_Service.iServicePrice);
	return m_pSQLDataAccessHelper->ExecuteNonQuery(cstrQuery);
}