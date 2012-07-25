
// customdialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "stdafx.h"

// CcustomdialogApp:
// See customdialog.cpp for the implementation of this class
//

class CcustomdialogApp : public CWinAppEx
{
private:
	ULONG_PTR   m_gdiplusToken;
	
public:
	CcustomdialogApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CcustomdialogApp theApp;