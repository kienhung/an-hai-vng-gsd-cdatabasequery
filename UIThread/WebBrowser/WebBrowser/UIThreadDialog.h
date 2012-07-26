#pragma once
#include "explorer.h"


// CUIThreadDialog dialog

class CUIThreadDialog : public CDialog
{
	DECLARE_DYNAMIC(CUIThreadDialog)

public:
	CUIThreadDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUIThreadDialog();

// Dialog Data
	enum { IDD = IDD_UITHREAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CExplorer m_explorer;
};
