
// CustomDialogDlg.h : header file
//

#pragma once
#include "Custombutton.h"
#include "explorer1.h"


// CCustomDialogDlg dialog
class CCustomDialogDlg : public CDialog
{
// Construction
public:
	CCustomDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CUSTOMDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	Image m_image;

	bool m_bIsPress;

	int m_imageX;
	int m_imageY;

	int m_iTitleBarWidth;
	int m_iTitleBarHeigth;

	CCustomButton m_myButton;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedMyButton();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

};
