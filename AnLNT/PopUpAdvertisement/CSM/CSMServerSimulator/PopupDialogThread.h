#pragma once
#include "PopupDlg.h"


// CPopupDialogThread

class CPopupDialogThread : public CWinThread
{
	DECLARE_DYNCREATE(CPopupDialogThread)

protected:
	CPopupDialogThread();           // protected constructor used by dynamic creation
	virtual ~CPopupDialogThread();

	CPopupDlg m_popupDialog;
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


