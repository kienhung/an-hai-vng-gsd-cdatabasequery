/******************************************************************************
* Copyright (c) 2010 VNG Corp. All Rights Reserved.
*
* This is unpublished proprietary source code of VNG Corp.
* The copyright notice above does not evidence any actual or intended
* publication of such source code.
*
* File Name: MySQLConn.h
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

#pragma once

#include <mysql.h>

class CMySQLRes
{
private:
	MYSQL_RES		*m_pData;
	UINT64			m_ui64NumRow;
	UINT			m_uiNumField;
	CStringArray	m_arrFields;

public:
	CMySQLRes(void);
	~CMySQLRes(void);

	void SaveData(MYSQL_RES	*pData);
	UINT64 GetRowCount(){return m_ui64NumRow;}
	BOOL FetchRow();
	CString GetField(UINT uiIndex);
	UINT GetFieldCount(){return m_uiNumField;}
	void FreeResult();
};

class CMySQLConn
{
	friend class CCSMServerSimulatorApp;
private:
	MYSQL				*m_pMySQL;
	CRITICAL_SECTION	m_csAccessDB;
	static char			m_strPassword[64];

private:
	static BOOL GetMySQLPassword();
	inline char *ConvertIntoUTF8(const wchar_t *pWideChar);
public:
	CMySQLConn(void);
	~CMySQLConn(void);

	BOOL Connect(CString *pStrError = NULL);
	void DisConnect();
	BOOL ExecSelect(LPCTSTR lpQuery, CMySQLRes *pMySQLRes = NULL, CString *pStrError = NULL);
	BOOL ExecInsert(LPCTSTR lpQuery, UINT64 *pUI64InsertId = NULL, CString *pStrError = NULL);
	BOOL ExecUpdate(LPCTSTR lpQuery, UINT64 *pUI64AffectedRow = NULL, CString *pStrError = NULL);
	BOOL Exec(LPCTSTR lpQuery, CString *pStrError = NULL);
};
