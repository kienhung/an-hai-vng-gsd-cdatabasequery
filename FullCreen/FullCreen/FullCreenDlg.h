
// FullCreenDlg.h : header file
//

#pragma once

#include "TlHelp32.h"
#include "vector"
using namespace std;

#define	IDT_TIMER_0	WM_USER + 200
#define	IDT_TIMER_1	IDT_TIMER_0 + 1

typedef struct INFOPROCESS
{
	PROCESSENTRY32 EntryProcess;
	HANDLE hProcess;
}INFOPROCESS;

// CFullCreenDlg dialog
class CFullCreenDlg : public CDialog
{
// Construction
	LPCREATESTRUCT m_lpCreateStruct;

	DWORD m_ProIDFifa;
	HANDLE m_hMainFifa;
	DWORD m_ThreadIDFifa;
	PROCESSENTRY32 m_Fifa;
	vector<INFOPROCESS> m_lstProcessEntryFifa;
	
public:
	CFullCreenDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_FULLCREEN_DIALOG };

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
	afx_msg void OnBnClickedBtnFullcreen();
	afx_msg void OnBnClickedBtnNormal();
	/*UINT SetTimer(UINT_PTR nIDEvent, UINT nElapse, 
		void (CALLBACK EXPORT* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD));*/
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnKillFocus(CWnd* pNewWnd);
	PROCESSENTRY32 GetProIDFifa();


protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnFifa();
	afx_msg void OnBnClickedBtnMinimizepid();
	
	afx_msg void OnBnClickedBtnRestore();
	afx_msg void OnBnClickedBtnGetpid();
	//DWORD TryGetProcessIDbyProcessHandle(HANDLE hProcess);
	
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedBtnResotrenormal();
};
