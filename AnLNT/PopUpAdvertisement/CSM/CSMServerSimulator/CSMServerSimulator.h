// CSMServerSimulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "MyUtils.h"
#include "Listener.h"
#include "MySQLConn.h"

// CCSMServerSimulatorApp:
// See CSMServerSimulator.cpp for the implementation of this class
//

class CCSMServerSimulatorApp : public CWinApp
{
public:
	CCSMServerSimulatorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CCSMServerSimulatorApp theApp;
extern CListener g_Listener;
extern CMySQLConn g_MySQLConn;