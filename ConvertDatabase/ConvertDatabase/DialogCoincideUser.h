#pragma once
#pragma warning(disable :4520 )
#include "MyStruct.h"

// CDialogCoincideUser dialog

class CDialogCoincideUser : public CDialog
{
	DECLARE_DYNAMIC(CDialogCoincideUser)

public:
	CDialogCoincideUser(CWnd* pParent = NULL);   // standard constructor
	CDialogCoincideUser(CWnd* pParent = NULL, CSM_USER* csm_User = NULL, BOOL* optionSave = FALSE);
	virtual ~CDialogCoincideUser();

// Dialog Data
	enum { IDD = IDD_DLG_LIKEUSER };

protected:
	CSM_USER* m_csmUser;
	BOOL* m_optionSave;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
