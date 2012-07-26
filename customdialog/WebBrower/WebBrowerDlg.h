
// WebBrowerDlg.h : header file
//

#pragma once
#include "ie_webbrower.h"
#include "CustomGroupBox.h"

// CWebBrowerDlg dialog
class CWebBrowerDlg : public CDialog
{
// Construction
public:
	CWebBrowerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WEBBROWER_DIALOG };

	static DWORD WINAPI ThreadLoadWebPage( LPVOID lpParam );
	static DWORD WINAPI ThreadLoadWebPageFromOtherControl( LPVOID lpParam );
	HANDLE m_hThread1;
	HANDLE m_hThread2;
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
public:
	//CIe_WebBrower m_WebBrower;
	afx_msg void OnBnClickedBtnLoad();
	CCustomGroupBox m_Group;
	CIe_WebBrower m_Ie2;

};
