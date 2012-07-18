
// GetListFile.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGetListFileApp:
// See GetListFile.cpp for the implementation of this class
//

class CGetListFileApp : public CWinAppEx
{
public:
	CGetListFileApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGetListFileApp theApp;