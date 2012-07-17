
// RecursivelyRemoveFolderDlg.h : header file
//

#pragma once


// CRecursivelyRemoveFolderDlg dialog
class CRecursivelyRemoveFolderDlg : public CDialog
{
// Construction
public:
	CRecursivelyRemoveFolderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RECURSIVELYREMOVEFOLDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CEdit* m_edtFolder;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBrowsefolder();
	afx_msg void OnBnClickedBtnRemove();
};
