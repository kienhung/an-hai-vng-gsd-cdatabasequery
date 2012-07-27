
// FullCreenDlg.h : header file
//

#pragma once


#define	IDT_TIMER_0	WM_USER + 200
#define	IDT_TIMER_1	IDT_TIMER_0 + 1

// CFullCreenDlg dialog
class CFullCreenDlg : public CDialog
{
// Construction
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
	
};
