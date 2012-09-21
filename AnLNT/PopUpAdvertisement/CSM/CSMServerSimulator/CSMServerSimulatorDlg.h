// CSMServerSimulatorDlg.h : header file
//

#pragma once
#include "PopupDlg.h"
// CCSMServerSimulatorDlg dialog
class CCSMServerSimulatorDlg : public CDialog
{
// Construction
public:
	CCSMServerSimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CSMSERVERSIMULATOR_DIALOG };

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
	afx_msg LRESULT OnAsyncSocketNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();


protected:
	BOOL ShowPopupDlg();


protected:
	CPopupDlg m_popupDialog;
	BOOL m_bIsPopupDialogExist;

	int m_iXPopupDialog;
	int m_iYPopupDialog;
	int m_iWidthPopupDialog;
	int m_iHeightPopupDialog;

	int m_iStep;
	int m_iCurrentHeight;
	int m_bIsPopupDialogUping;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	static DWORD WINAPI MovePopupDialogThreadFunction(PVOID pvParam);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	void SetPopupDialogCoordinates();

	void AdjustPopupDialogPosition();

	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnUp();
};
