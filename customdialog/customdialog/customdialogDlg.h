
// customdialogDlg.h : header file
//

#pragma once
#include "ListCtrlEx.h"
using namespace Gdiplus;

// CcustomdialogDlg dialog
class CcustomdialogDlg : public CDialog
{
// Construction
public:
	CcustomdialogDlg(CWnd* pParent = NULL);	// standard constructor
	void InitListCtrl();
	BOOL InitImageList();
	void InsertItems();
// Dialog Data
	enum { IDD = IDD_CUSTOMDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	bool m_bIsPress;
	CPoint m_pOldPoint;
	CRect m_Rectangle;
	CListCtrlEx m_lstCtrlEx;
	CImageList	m_cImageListNormal;
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseHover(UINT nFlags, CPoint point);
	void DrawItemss(Graphics* graphics, CRect* rect);
};
