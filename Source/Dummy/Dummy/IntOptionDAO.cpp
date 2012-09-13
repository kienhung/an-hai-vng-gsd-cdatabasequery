#include "StdAfx.h"
#include "IntOptionDAO.h"

CIntOptionDAO::CIntOptionDAO(void)
{
	m_pSQLDataAccessHelper = NULL;
}

CIntOptionDAO::~CIntOptionDAO(void)
{
	if (NULL != m_pSQLDataAccessHelper)
	{
		delete m_pSQLDataAccessHelper ;
	}
}

BOOL CIntOptionDAO::ConnectToDB(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	if (m_pSQLDataAccessHelper != NULL)
	{
		delete m_pSQLDataAccessHelper;
	}
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
	return m_pSQLDataAccessHelper->IsConnected();
}
CString CIntOptionDAO::GetLicesenID()
{
	
	
	if(!ConnectToDB("root","","localhost","ddm"))
	{
		return NULL;
	}
	


	CStringA cstrSelectQuery("SELECT Value FROM intoptiontb where OptionName = 'nlcid';");

	MYSQL_RES *pMySQLQueryResult =  m_pSQLDataAccessHelper->ExecuteQuery(cstrSelectQuery);

	if(NULL == pMySQLQueryResult)
	{
		return FALSE;
	}

	MYSQL_ROW mySQLResultRow;
	if((mySQLResultRow = mysql_fetch_row(pMySQLQueryResult)))
	{
		CStringA strTemp(mySQLResultRow[0]);
		CString strLicenseID(strTemp);
		m_pSQLDataAccessHelper->FreeQueryResult(pMySQLQueryResult);
		return strLicenseID;
	}

	m_pSQLDataAccessHelper->FreeQueryResult(pMySQLQueryResult);
	return NULL;
}
