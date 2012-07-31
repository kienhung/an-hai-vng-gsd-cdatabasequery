
// CustomDialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCustomDialogApp:
// See CustomDialog.cpp for the implementation of this class
//

class CCustomDialogApp : public CWinAppEx
{
protected:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
public:
	CCustomDialogApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCustomDialogApp theApp;