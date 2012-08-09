#pragma once
#include "StdAfx.h"
#include "ConvertDB.h"
#include "BlackListDAO.h"
#include "UserDAO.h"
#include "ServiceDAO.h"
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

BOOL CConvertDB::Convert(const TCHAR* strPath)
{
	if(!Connect(strPath))
	{
		AfxMessageBox(_T("Không thể kết nối cơ sở dữ liệu"), 0, 0);
		return FALSE;
	}
	
	/*if(!ConvertBlackList())
	{
		return FALSE;
	}
	if(!ConvertUser())
	{
		return FALSE;
	}*/
	if(!ConvertService())
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CConvertDB::Connect(const TCHAR* strPath)
{
	
	CString strConnect;
	strConnect.Format(_T("ODBC;Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s ;Uid=Admin;Pwd=MASOTHUY0101148362;"), strPath );
	//StringCchPrintf(strConnect.GetBuffer(), MAX_PATH + 20, _T("ODBC;Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ= ;Uid=Admin;Pwd=;"));
    //BOOL kq =  m_db.OpenEx(strConnect, CDatabase::openReadOnly | CDatabase::noOdbcDialog);
	//return m_db.OpenEx(strConnect.GetBuffer(), CDatabase::openReadOnly |CDatabase::noOdbcDialog);
	return m_db.Open(NULL, false, false, strConnect);
}


VOID CConvertDB::VariantToCstring(const CDBVariant &var, CString &sData)
{
	switch (var.m_dwType)
    {
        case DBVT_STRING:
            sData.Format(_T("%s"), var.m_pstring->GetBuffer(var.m_pstring->GetLength()));
            break;
        case DBVT_ASTRING:
            sData.Format(_T("%s"), var.m_pstringA->GetBuffer(var.m_pstringA->GetLength()));
            break;
        case DBVT_WSTRING:
            sData.Format(_T("%s"), var.m_pstringW->GetBuffer(var.m_pstringW->GetLength()));
            break;
		case DBVT_BOOL:
			sData.Format(_T("%d"), var.m_boolVal);
			break;		
		case DBVT_SHORT:
			sData.Format(_T("%d"), var.m_iVal);
			break;
		case DBVT_LONG:
			sData.Format(_T("%d"), var.m_lVal);
			break;
		case DBVT_UCHAR:
			sData.Format(_T("%d"), var.m_chVal);
			break;
		case DBVT_DOUBLE:
			sData.Format(_T("%f"), var.m_dblVal);
			break;
		case DBVT_DATE:
			sData.Format(_T("%d-%d-%d %d:%d:%d"), var.m_pdate->year, var.m_pdate->month, var.m_pdate->day, var.m_pdate->hour, var.m_pdate->minute, var.m_pdate->second);
			break;
        default:
            sData = _T("");
   }
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

		CBlackListDAO backListDAO;
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
			
			
			BLACKLIST backList;
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


BOOL CConvertDB::ConvertService()
{
	LPCTSTR query = _T("SELECT Menuname,MenuCost  FROM MenuItem;");
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

		

		CServiceDAO serviceDAO;
		if(!serviceDAO.ConnectToDB(m_ConnectStringToMYSQL.m_strUsername,
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
			CSM_SERVICE csm_Service;
			
			// Get MenuName
			rs.GetFieldValue( _T("Menuname"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_Service.strServiceName, MAX_SERVICENAME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();
			
			// Get MenuCost
			rs.GetFieldValue( _T("MenuCost"), var);
			csm_Service.iServicePrice = var.m_dblVal;
			
			if(!serviceDAO.AddService(csm_Service))
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


BOOL CConvertDB::ConvertUser()
{
	LPCTSTR query = _T("SELECT Hoten,Username,Type,RecordDate,ExpiredDate,Address,phone,Email,IDCard,RemainTime,TimeUsed,FreeMinutes FROM Member WHERE Type=2;");
	TRY
	{
		CRecordset rs(&m_db);
		if(!rs.Open(CRecordset::dynaset, query, CRecordset::none))
		{
			return FALSE;
		}
		short sFieldCount = rs.GetODBCFieldCount();

		
		
		CUserDAO userDAO;
		if(!userDAO.ConnectToDB(m_ConnectStringToMYSQL.m_strUsername,
									m_ConnectStringToMYSQL.m_strPasssword,
									m_ConnectStringToMYSQL.m_strServerAddress,
									m_ConnectStringToMYSQL.m_strDatabaseName)
			)
		{
			AfxMessageBox(_T("Không thể kết nối cơ sở dữ liệu của csm server"), MB_ICONSTOP);
			return FALSE;
		}

		CDBVariant var;
		CString strValue;

		
		while (!rs.IsEOF())
		{
			CSM_USER csm_User;
			// Get Fullname
			rs.GetFieldValue(_T("Hoten"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strName, MAX_NAME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();


			// Get Username
			rs.GetFieldValue(_T("Username"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strUsername, MAX_USERNAME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Set (get) UserType
			StringCchPrintf(csm_User.strUserType, 3, _T("2"));
			
			// Get RecordDate
			rs.GetFieldValue(_T("RecordDate"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strRecordDate, MAX_STRINGDATE, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get ExpiredDate
			rs.GetFieldValue(_T("ExpiredDate"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strExpiryDate, MAX_STRINGDATE, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get Address
			rs.GetFieldValue(_T("Address"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strAddress, MAX_ADDRESS, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get Phone
			rs.GetFieldValue(_T("phone"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strPhone, MAX_PHONE, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get Email
			rs.GetFieldValue(_T("Email"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strEmail, MAX_EMAIL, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get RemainTime
			rs.GetFieldValue(_T("RemainTime"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strRemainTime, MAX_INTTIME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get TimeUsed
			rs.GetFieldValue(_T("TimeUsed"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strTimeUsed, MAX_INTTIME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			// Get FreeMinutes
			rs.GetFieldValue(_T("FreeMinutes"), var);
			VariantToCstring(var, strValue);
			StringCchPrintf(csm_User.strFreeTime, MAX_INTTIME, _T("%s"), strValue.GetBuffer());
			strValue.Empty();
			var.Clear();

			//Insert user to csm db
			if(!userDAO.AddUser(csm_User))
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