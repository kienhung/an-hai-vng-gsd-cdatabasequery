#pragma once
#include "StdAfx.h"
#include "ConvertDB.h"
#include "BackListDAO.h"
#include "Strsafe.h"
#include "StringConverter.h"

CConvertDB::CConvertDB(void)
{
	StringCchPrintfA(m_ConnectStringToMYSQL.m_strUsername, MAX_LENGTH, "%s", "root");
	StringCchPrintfA(m_ConnectStringToMYSQL.m_strPasssword, MAX_LENGTH, "%s", "hai");
	StringCchPrintfA(m_ConnectStringToMYSQL.m_strServerAddress, MAX_LENGTH, "%s", "localhost");
	StringCchPrintfA(m_ConnectStringToMYSQL.m_strDatabaseName, MAX_LENGTH, "%s", "ddm");
}

CConvertDB::~CConvertDB(void)
{
}


void CConvertDB::Convert(const TCHAR* strPath)
{
	if(!Connect(strPath))
	{
		AfxMessageBox(_T("Không thể kết nối cơ sở dữ liệu"), 0, 0);
		return;
	}
	ConvertBlackList();
}

BOOL CConvertDB::Connect(const TCHAR* strPath)
{
	
	CString strConnect;
	strConnect.Format(_T("ODBC;Driver={Microsoft Access Driver (*.mdb)};DBQ=%s ;Uid=Admin;Pwd=;"), strPath );
	//StringCchPrintf(strConnect.GetBuffer(), MAX_PATH + 20, _T("ODBC;Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ= ;Uid=Admin;Pwd=;"));
    //BOOL kq =  m_db.OpenEx(strConnect, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
	
	return m_db.Open(NULL, false, false, strConnect);
}

BOOL CConvertDB::ConvertBlackList()
{
	LPCTSTR query = _T("SELECT BlackList.[Address],BlackList.[DateAdd], BlackList.[Status], BlackList.[Admin]  FROM BlackList;");
	TRY
	{
		CRecordset rs(&m_db);
		if(!rs.Open(CRecordset::dynaset, query, CRecordset::none))
		{
			return FALSE;
		}
		short sFieldCount = rs.GetODBCFieldCount();

		CDBVariant var;
		CString strValue;

		CBackListDAO backListDAO;
		if(!backListDAO.ConnectToDB(m_ConnectStringToMYSQL.m_strUsername,
									m_ConnectStringToMYSQL.m_strPasssword,
									m_ConnectStringToMYSQL.m_strServerAddress,
									m_ConnectStringToMYSQL.m_strDatabaseName)
			)
		{
			AfxMessageBox(_T("Không thể kết nối cơ sở dữ liệu của csm server"), MB_ICONSTOP);
			return FALSE;
		}
		//CString strValue;
		
		while (!rs.IsEOF())
		{
			
			
			BACKLIST backList;
			// Get value "Address"
			rs.GetFieldValue( _T("Address"), var);
			switch(var.m_dwType)
			{
				case DBVT_STRING:
                        StringCchPrintf(backList.strURL, MAX_PATH, _T("%s"), var.m_pstring->GetBuffer(var.m_pstring->GetLength()));
                        break;
                    case DBVT_ASTRING:
                        StringCchPrintf(backList.strURL, MAX_PATH, _T("%s"),  var.m_pstringA->GetBuffer(var.m_pstringA->GetLength()));
                        break;
                    case DBVT_WSTRING:
                        StringCchPrintf(backList.strURL, MAX_PATH, _T("%s"),  var.m_pstringW->GetBuffer(var.m_pstringW->GetLength()));
                        break;
                    default:
                        StringCchPrintf(backList.strURL, MAX_PATH, _T(""));
			}

			// Get value "DateAdd"
			rs.GetFieldValue( _T("DateAdd"), var);
			
			CString strDateTime;
			strDateTime.Format(_T("%d-%d-%d %d:%d:%d"), var.m_pdate->year, var.m_pdate->month, var.m_pdate->day,
														var.m_pdate->hour, var.m_pdate->minute, var.m_pdate->second);

			StringCchPrintf(backList.strRecordDate, MAX_STRINGDATE, _T("%s"), strDateTime.GetBuffer());

			// Get value "Status"
			rs.GetFieldValue( _T("Status"), var);
			if(var.m_dwType == DBVT_BOOL)
			{
				if(var.m_boolVal)
				{
					backList.iActive = 1;
				}
				else
					backList.iActive = 0;
			}

			// Get value "Admin"
			rs.GetFieldValue( _T("Admin"), var);
			if(var.m_dwType == DBVT_BOOL)
			{
				if(var.m_boolVal)
				{
					backList.iAddedBy = 1;
				}
				else
					backList.iAddedBy = 0;
			}
			if(!backListDAO.AddBackList(backList))
			{
				AfxMessageBox(_T("insert fail"));
			}
			// Next record
			rs.MoveNext();
		}
	}
	CATCH_ALL(e)
	{
		TCHAR  errMsg[255];
		e->GetErrorMessage(errMsg, 255);
		AfxMessageBox(errMsg, MB_ICONSTOP, 0);
	}
	END_CATCH_ALL
	return TRUE;
}