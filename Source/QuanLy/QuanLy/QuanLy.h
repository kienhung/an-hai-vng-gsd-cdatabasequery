
// QuanLy.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "mysqlnhanviendao.h"

#define MAX_LENGTH 50
// CQuanLyApp:
// See QuanLy.cpp for the implementation of this class
//
typedef struct	
	{
		bool m_bIsConnected;
		char m_strUsername[MAX_LENGTH];
		char m_strPasssword[MAX_LENGTH];
		char m_strServerAddress[MAX_LENGTH];
		char m_strDatabaseName[MAX_LENGTH];
	}CONNECTSTRING;
class CQuanLyApp : public CWinAppEx
{
public:
	CQuanLyApp();
	CONNECTSTRING ConnectString;
// Overrides
	public:
	virtual BOOL InitInstance();
	bool Connect();
// Implementation

	DECLARE_MESSAGE_MAP()
	BOOL ExitInstance(void);
};

extern CQuanLyApp theApp;