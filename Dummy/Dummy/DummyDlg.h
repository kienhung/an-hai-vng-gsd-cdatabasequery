
// DummyDlg.h : header file
//

#pragma once
#include "TrayDialog.h"
#include "ExplorerRegInfo.h"

// CDummyDlg dialog
class CRegisterInfoDlg : public CTrayDialog
{
// Construction
public:
	CRegisterInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DLG_REGISTERINFO };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnTrayMenuRegisterInfo();
	afx_msg void OnTrayMenuAbout();
	afx_msg void OnTrayMenuExit();

public:
	CExplorer_reginfo m_webBrowerRegInfo;
};
