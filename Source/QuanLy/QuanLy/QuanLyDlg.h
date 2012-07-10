
// QuanLyDlg.h : header file
//

#pragma once


// CQuanLyDlg dialog
class CQuanLyDlg : public CDialog
{
// Construction
public:
	CQuanLyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_QUANLY_DIALOG };
	CListCtrl	m_lstNhanVien;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	void InitListCtrlCols();

	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
};
