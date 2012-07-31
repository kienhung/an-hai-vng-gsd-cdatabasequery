
// ListControlDlg.h : header file
//

#pragma once


// CListControlDlg dialog
class CListControlDlg : public CDialog
{
// Construction
public:
	CListControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LISTCONTROL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CListCtrl *m_pListCtrl;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnIcon();
	afx_msg void OnBnClickedBtnSmallicon();
	afx_msg void OnBnClickedBtnList();
	afx_msg void OnBnClickedBtnReport();
};
