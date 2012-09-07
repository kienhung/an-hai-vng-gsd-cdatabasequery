#pragma once
#include "StdAfx.h"
#include "MySQLDataAccessHelper.h"
#include "StringConverter.h"

CMySQLDataAccessHelper::CMySQLDataAccessHelper(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort)
{
	
	m_mySQLConnection = mysql_init(NULL);
	if (NULL == m_mySQLConnection) {
		m_bIsConnected = FALSE;
		return;
	}
	
	if (mysql_options(m_mySQLConnection, MYSQL_SET_CHARSET_NAME, "utf8"))
	{
		m_bIsConnected = FALSE;
		return;
	}
	if(strlen(strPassword) == 0)
	{
		
		
		char strPass[30] = {0};
		GetPassWordMySQL(&strPass[0]);
		


		if (NULL == mysql_real_connect(m_mySQLConnection, strServerAddress, strUser, strPass, strDatabase, uiPort, NULL, 0)) 
		{
			m_bIsConnected = FALSE;
			return;
		}
	}

	
	if (NULL == mysql_real_connect(m_mySQLConnection, strServerAddress, strUser, strPassword, strDatabase, uiPort, NULL, 0)) {
		m_bIsConnected = FALSE;
		return;
	}
	m_bIsConnected = TRUE;
}

CMySQLDataAccessHelper::~CMySQLDataAccessHelper(void)
{
	if (NULL != m_mySQLConnection) {
		mysql_close(m_mySQLConnection);
	}
}

VOID CMySQLDataAccessHelper::Disconnect()
{
	if (NULL != m_mySQLConnection) {
		mysql_close(m_mySQLConnection);
	}
}

BOOL CMySQLDataAccessHelper::IsConnected()
{
	return m_bIsConnected;
}

MYSQL_RES* CMySQLDataAccessHelper::ExecuteQuery(const char *strQuery) {

	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		
		//throw new CMyException("Failure to execute query", MY_SQL);
		AfxMessageBox(_T("Failure to execute query"), MB_ICONSTOP, 0);
		return NULL;
	}
	
	MYSQL_RES *pMySQLQueryResult = mysql_store_result(m_mySQLConnection);
	if (NULL == pMySQLQueryResult) {
		//throw new CMyException("Failure to get results of the query", MY_SQL);
		AfxMessageBox(_T("Failure to get results of the query"), MB_ICONSTOP, 0);
		return NULL;
	}
	return pMySQLQueryResult;
}


void CMySQLDataAccessHelper::FreeQueryResult(MYSQL_RES *pMySQLQueryResult) {
	mysql_free_result(pMySQLQueryResult);
	
}

BOOL CMySQLDataAccessHelper::ExecuteNonQuery(const char *strQuery) {
	if (0 != mysql_query(m_mySQLConnection, strQuery)) {
		//throw new CMyException("Failure to execute query", MY_SQL);
		//AfxMessageBox(_T("Failure to execute query"), MB_ICONSTOP, 0);
		return FALSE;
	}
	return TRUE;
}

bool CMySQLDataAccessHelper::CheckUser(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort) {

	MYSQL *mySQLConnection = mysql_init(NULL);
	if (NULL == mySQLConnection) {
		return false;
	}
	bool bFresult = true;
	if (NULL ==	mysql_real_connect(mySQLConnection, strServerAddress, strUser, strPassword, NULL, uiPort, NULL, 0)) {
		bFresult = false;
	}
	mysql_close(mySQLConnection);
	return bFresult;
}

VOID CMySQLDataAccessHelper::GetPassWordMySQL(char* strOutPass)
{
	HKEY	hKey;
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\TekWaveSolutions\\CyberStationManager\\ServerData"),
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS
		)
	{
		return;
	}

	TCHAR szStringValue[30] = {0};
	LONG lResult = 0;
	DWORD dwSize=0;
	DWORD dwType = REG_SZ;
	lResult = RegQueryValueEx(hKey, _T("MYSQLPWD"), 0, &dwType, NULL, &dwSize);
	if (lResult != ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return;	
	}
	RegQueryValueEx(hKey, _T("MYSQLPWD"), 0, &dwType, (LPBYTE)szStringValue, &dwSize);
	RegCloseKey(hKey);
	TCHAR	strTempPass[30] = {0};
	CString strDecodePass;
	DeCodeString(szStringValue, strDecodePass);

	CStringConverter stringConverter;
	char* pBuffer = stringConverter.UnicodeToUTF8(strDecodePass.GetBuffer());

	char strTempBuffer[MAX_PATH] = {0};
	if(NULL != pBuffer)
	{
		strcpy_s(strTempBuffer, MAX_PATH, pBuffer);
	}
	strOutPass = &strTempBuffer[0];
}

VOID CMySQLDataAccessHelper::DeCodeString(const CString &strIN, CString & strOUT)
{
	int iLength = strIN.GetLength();
	strOUT.GetBufferSetLength(iLength);

	for (int i = 0; i < iLength; i++)
	{
		if (i%3 == 0)
			  strOUT.SetAt(i, strIN.GetAt(i) - 5);
		else if(i%2 == 0)
			  strOUT.SetAt(i, strIN.GetAt(i) + 3);
		else if(i%5 == 0)
			  strOUT.SetAt(i, strIN.GetAt(i) - 7);
		else
			  strOUT.SetAt(i, strIN.GetAt(i) + 2);
	}
}
