#pragma once

#include "MyWebBrowserDlg.h"

// CUIThread

class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)

protected:
	CUIThread();           // protected constructor used by dynamic creation
	virtual ~CUIThread();
	CMyWebBrowserDlg myWebDlg;
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


