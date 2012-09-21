/******************************************************************************
* Copyright (c) 2010 VNG Corp. All Rights Reserved.
*
* This is unpublished proprietary source code of VNG Corp.
* The copyright notice above does not evidence any actual or intended
* publication of such source code.
*
* File Name: MySQLConn.cpp
*
* Description: 
* 
* Author: DiepTH
*
* Creation: (mm/dd/yyyy)
* 07/01/2009, DiepTH,   Create this class. 
* Change history: (mm/dd/yyyy)
* 
******************************************************************************/

#include "StdAfx.h"
#include "CSMServerSimulator.h"
#include "MySQLConn.h"
#include "Registry.h"

#define	MYSQL_HOST			"127.0.0.1"
#define MYSQL_USER			"root"
#define MYSQL_DB_NAME		"ddm"
#define MYSQL_PORT			3306
#define	REG_MYSQL_PASS		_T("MYSQLPWD")

CMySQLRes::CMySQLRes(void)
{	
	m_pData = NULL; 
	m_ui64NumRow = 0;
	m_uiNumField = 0;
}

CMySQLRes::~CMySQLRes(void)
{
	if (m_pData) 
		mysql_free_result(m_pData); 
	m_pData = NULL;
};

void CMySQLRes::SaveData(MYSQL_RES	*pData)
{
	m_pData = pData;
	m_ui64NumRow = mysql_num_rows(m_pData);
	m_uiNumField = mysql_num_fields(m_pData);
}

void CMySQLRes::FreeResult()
{
	if (m_pData)
	{
		mysql_free_result(m_pData);
		m_pData = NULL;
	}
	m_ui64NumRow = 0;
	m_arrFields.RemoveAll();
	m_uiNumField = 0;
}

/****************************************************************************
* Description: Retrieves the next row of the MySQL result set. 
* Input:	None.
* Output:	None.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLRes::FetchRow()
{
	m_arrFields.RemoveAll();

	if (!m_pData)
		return FALSE;

	MYSQL_ROW	row;
	row = mysql_fetch_row(m_pData);

	if (!row)
		return FALSE;

	int		iLen, 
			iNumChar;
	m_arrFields.SetSize(m_uiNumField);
	for (UINT i = 0; i < m_uiNumField; i++)
	{
		if (row[i] && row[i][0])
		{
#ifdef _UNICODE
			iLen = strlen(row[i]);
			iNumChar = MultiByteToWideChar(CP_UTF8, 0, row[i], iLen, NULL, 0);
			MultiByteToWideChar(CP_UTF8, 0, row[i], iLen, m_arrFields[i].GetBufferSetLength(iNumChar), iNumChar);
#else
			m_arrFields[i] = row[i];
#endif
		}
		else
		{
			m_arrFields[i] = _T("");
		}
	}

	return TRUE;
}

/****************************************************************************
* Description: Get value of a field of the current retrieved row in the MySQL result set. 
* Input:	UINT uiIndex:	order of the field in the calling query string.
* Output:	None.
* Return:	Value of the field.
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
CString CMySQLRes::GetField(UINT uiIndex)
{
	if (uiIndex >= m_uiNumField)
		return _T("");

	return m_arrFields.GetAt(uiIndex);
}

// CMySQLConn class
char CMySQLConn::m_strPassword[] = {0};
CMySQLConn::CMySQLConn(void)
{
	m_pMySQL = NULL;
	InitializeCriticalSection(&m_csAccessDB);
}

CMySQLConn::~CMySQLConn(void)
{
	DisConnect();
	DeleteCriticalSection(&m_csAccessDB);
}

/****************************************************************************
* Description: Open a connection to the MySQL database server. 
* Input:	None
* Output:	CString *pStrError:		store error string if failed.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::Connect(CString *pStrError)
{
	m_pMySQL = mysql_init(NULL);

	if (!m_pMySQL)
	{
		if (pStrError)
			*pStrError = _T("Create MYSQL connection object failed!");
		return FALSE;
	}
	if (mysql_options(m_pMySQL, MYSQL_SET_CHARSET_NAME, "utf8"))
	{
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("Set MYSQL option: %s."), strTmp);
		}
		return FALSE;
	}

	GetMySQLPassword();

	if (mysql_real_connect(m_pMySQL, MYSQL_HOST, MYSQL_USER, m_strPassword, MYSQL_DB_NAME, MYSQL_PORT, NULL, 0) == NULL)
	{
		mysql_close(m_pMySQL);
		m_pMySQL = NULL;
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("Connect MYSQL: %s."), strTmp);
		}
		return FALSE;
	}
	
	m_pMySQL->reconnect = 1;

	return TRUE;
}

/****************************************************************************
* Description: Close the connection to the MySQL database server. 
* Input:	None.
* Output:	None.
* Return:	None.
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
void CMySQLConn::DisConnect()
{
	if (m_pMySQL)
	{
		mysql_close(m_pMySQL);
		m_pMySQL = NULL;
	}
}

/****************************************************************************
* Description: Execute a select query. 
* Input:	LPCTSTR lpQuery:		Query string.
* Output:	CMySQLRes *pMySQLRes:	A pointer to a object which stores the query result.
*			CString *pStrError:		store error string if failed.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::ExecSelect(LPCTSTR lpQuery, CMySQLRes *pMySQLRes, CString *pStrError)
{
	
	char	*pUTF8Str;
	int		iRet;

	if  (!lpQuery || !lpQuery[0])
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Invalid parameter!");
		return FALSE;
	}

#ifdef UNICODE
	pUTF8Str = ConvertIntoUTF8(lpQuery);
	if (!pUTF8Str)
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Convert string into UTF8 failed!");
		return FALSE;
	}
#else
	pUTF8Str = lpQuery;
#endif

	EnterCriticalSection(&m_csAccessDB);
	iRet = mysql_query(m_pMySQL, pUTF8Str);
#ifdef UNICODE
	delete []pUTF8Str;
#endif

	if (iRet)
	{
		// Query failed
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("MYSQL execution: %s."), strTmp);
		}
		LeaveCriticalSection(&m_csAccessDB);
		return FALSE;
	}

	if (pMySQLRes)
	{
		MYSQL_RES	*pRes = mysql_store_result(m_pMySQL);
		if (pRes)
			pMySQLRes->SaveData(pRes);
		else 
		{
			 if (mysql_field_count(m_pMySQL))
			 {
				// mysql_store_result() should have returned data 
				if (pStrError)
				{
					CString	strTmp(mysql_error(m_pMySQL));
					pStrError->Format(_T("MYSQL execution: %s."), strTmp);
				}
				LeaveCriticalSection(&m_csAccessDB);
				return FALSE;
			 }
		}
	}
	else
	{
		// must do this
		MYSQL_RES *pRes = mysql_store_result(m_pMySQL);
		if (pRes)
			mysql_free_result(pRes);
	}
	
	LeaveCriticalSection(&m_csAccessDB);

	return TRUE;
}

/****************************************************************************
* Description: Execute a insert query. 
* Input:	LPCTSTR lpQuery:		Query string.
* Output:	UINT64 *pUI64InsertId:	A pointer to a UINT64 which stores inserted ID.
*			CString *pStrError:		store error string if failed.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::ExecInsert(LPCTSTR lpQuery, UINT64 *pUI64InsertId, CString *pStrError)
{


	char	*pUTF8Str;
	int		iRet;

	if  (!lpQuery || !lpQuery[0])
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Invalid parameter!");
		return FALSE;
	}

#ifdef UNICODE
	pUTF8Str = ConvertIntoUTF8(lpQuery);
	if (!pUTF8Str)
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Convert string into UTF8 failed!");
		return FALSE;
	}
#else
	pUTF8Str = lpQuery;
#endif

	EnterCriticalSection(&m_csAccessDB);
	iRet = mysql_query(m_pMySQL, pUTF8Str);
#ifdef UNICODE
	delete []pUTF8Str;
#endif

	if (iRet)
	{
		// Query failed
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("MYSQL execution: %s."), strTmp);
		}
		LeaveCriticalSection(&m_csAccessDB);
		return FALSE;
	}

	if (pUI64InsertId)
		*pUI64InsertId = mysql_insert_id(m_pMySQL);

	LeaveCriticalSection(&m_csAccessDB);

	return TRUE;
}
	
/****************************************************************************
* Description: Execute a update query. 
* Input:	LPCTSTR lpQuery:			Query string.
* Output:	UINT64 *pUI64AffectedRow:	A pointer to a UINT64 which stores number of affected rows.
*			CString *pStrError:			store error string if failed.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::ExecUpdate(LPCTSTR lpQuery, UINT64 *pUI64AffectedRow, CString *pStrError)
{

	char	*pUTF8Str;
	int		iRet;

	if  (!lpQuery || !lpQuery[0])
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Invalid parameter!");
		return FALSE;
	}

#ifdef UNICODE
	pUTF8Str = ConvertIntoUTF8(lpQuery);
	if (!pUTF8Str)
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Convert string into UTF8 failed!");
		return FALSE;
	}
#else
	pUTF8Str = lpQuery;
#endif

	EnterCriticalSection(&m_csAccessDB);
	iRet = mysql_query(m_pMySQL, pUTF8Str);
#ifdef UNICODE
	delete []pUTF8Str;
#endif

	if (iRet)
	{
		// Query failed
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("MYSQL execution: %s."), strTmp);
		}
		LeaveCriticalSection(&m_csAccessDB);
		return FALSE;
	}

	if (pUI64AffectedRow)
		*pUI64AffectedRow = mysql_affected_rows(m_pMySQL);

	LeaveCriticalSection(&m_csAccessDB);

	return TRUE;
}

/****************************************************************************
* Description: Execute a normal query (delete, ...). 
* Input:	LPCTSTR lpQuery:		Query string.
* Output:	CString *pStrError:		store error string if failed.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::Exec(LPCTSTR lpQuery, CString *pStrError)
{
	char	*pUTF8Str;
	int		iRet;

	if  (!lpQuery || !lpQuery[0])
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Invalid parameter!");
		return FALSE;
	}

#ifdef UNICODE
	pUTF8Str = ConvertIntoUTF8(lpQuery);
	if (!pUTF8Str)
	{
		if (pStrError)
			*pStrError = _T("MYSQL execution: Convert string into UTF8 failed!");
		return FALSE;
	}
#else
	pUTF8Str = lpQuery;
#endif

	EnterCriticalSection(&m_csAccessDB);
	iRet = mysql_query(m_pMySQL, pUTF8Str);
#ifdef UNICODE
	delete []pUTF8Str;
#endif

	if (iRet)
	{
		// Query failed
		if (pStrError)
		{
			CString	strTmp(mysql_error(m_pMySQL));
			pStrError->Format(_T("MYSQL execution: %s."), strTmp);
		}
		LeaveCriticalSection(&m_csAccessDB);
		return FALSE;
	}

	LeaveCriticalSection(&m_csAccessDB);

	return TRUE;
}

/****************************************************************************
* Description: Convert a wide character string to a UTF8 string. 
* Input:	const wchar_t *pWideChar:	The wide character string to convert.
* Output:	None.
* Return:	The UTF8 string if successful; otherwise NULL
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
inline char* CMySQLConn::ConvertIntoUTF8(const wchar_t *pWideChar)
{
	char	*pUTF8Str;
	int		iLen,
			iNumByte = 0;

	iLen = wcslen(pWideChar);
	iNumByte = WideCharToMultiByte(CP_UTF8, 0, pWideChar, iLen, NULL, 0, NULL, NULL);

	if (iNumByte <= 0)
		return NULL;

	pUTF8Str = new char[iNumByte + 1];
	if (!pUTF8Str)
		return NULL;

	WideCharToMultiByte(CP_UTF8, 0, pWideChar, iLen, pUTF8Str, iNumByte, NULL, NULL);
	pUTF8Str[iNumByte] = 0;

	return pUTF8Str;
}

/****************************************************************************
* Description: Read MySQL password from the registry. 
* Input:	None.
* Output:	None.
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		07/20/09	Author: DiepTH 
*****************************************************************************/
BOOL CMySQLConn::GetMySQLPassword()
{
	if (!m_strPassword[0])
	{
		CRegistry	reg;
		TCHAR		strTmpPass[64] = {0};
		CString		strDecodePass;
		
		if (!reg.ReadValue(REG_MYSQL_PASS, strTmpPass, 63))
			return FALSE;
		CMyUtils::DeCodeString(strTmpPass, strDecodePass);
#ifdef UNICODE
		int	iLen = strDecodePass.GetLength(),
			iRet;
		iRet = WideCharToMultiByte(CP_ACP, 0, strDecodePass.GetBuffer(iLen), iLen, m_strPassword, sizeof(m_strPassword) - 1, NULL, NULL);
		m_strPassword[iRet] = 0;
#else
		strcpy(m_strPassword, strTmpPass);
#endif
	}

	return TRUE;
}

