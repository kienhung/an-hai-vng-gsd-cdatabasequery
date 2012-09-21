// CSMClientSimulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Connect.h"
#include "MyUtils.h"

// CCSMClientSimulatorApp:
// See CSMClientSimulator.cpp for the implementation of this class
//

class CCSMClientSimulatorApp : public CWinApp
{
public:
	CCSMClientSimulatorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCSMClientSimulatorApp theApp;
extern TCHAR		g_strAppPath[MAX_PATH];
extern TCHAR		g_strSysPath[MAX_PATH];
extern char			g_strServerIP[16];
extern CString		g_strVersion;
extern CString		g_strReleaseDate;
extern CConnect		g_Connect;