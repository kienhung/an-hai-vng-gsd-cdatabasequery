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

	void Initialize();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnAsyncSocketNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();



protected:
	CPopupDlg m_popupDialog;

	BOOL m_bIsPopupDialogExist;
	BOOL m_bIsMovePopupDialogThreadRunning;
	BOOL m_bIsMovePopupDialogThreadPausing;

	int m_iXPopupDialog;
	int m_iYPopupDialog;
	int m_iWidthPopupDialog;
	int m_iHeightPopupDialog;

	int m_iStep;
	int m_iCurrentHeight;

	BOOL m_bIsUp;
	HANDLE m_hMovePopupDialogThread;
public:

	static DWORD WINAPI MovePopupDialogThreadFunction(PVOID pvParam);
	BOOL SetPopupDialogCoordinates();


	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnKillthread();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
};
