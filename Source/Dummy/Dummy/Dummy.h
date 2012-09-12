// Dummy.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDummyApp:
// See Dummy.cpp for the implementation of this class
//

class CDummyApp : public CWinApp
{
private:
	HANDLE m_hMutex;
	void RunOnlyOneInst();
	BOOL ReregisterDialogClass();
	void StartProcessDummyLaucher();
public:
	CDummyApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDummyApp theApp;