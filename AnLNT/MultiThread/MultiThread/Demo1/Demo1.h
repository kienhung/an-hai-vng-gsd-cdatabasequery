
// Demo1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDemo1App:
// See Demo1.cpp for the implementation of this class
//

class CDemo1App : public CWinAppEx
{
public:
	CDemo1App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDemo1App theApp;