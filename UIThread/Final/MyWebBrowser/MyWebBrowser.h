
// MyWebBrowser.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyWebBrowserApp:
// See MyWebBrowser.cpp for the implementation of this class
//

class CMyWebBrowserApp : public CWinAppEx
{
protected:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
public:
	CMyWebBrowserApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyWebBrowserApp theApp;