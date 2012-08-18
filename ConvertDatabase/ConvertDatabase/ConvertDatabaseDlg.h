
// ConvertDatabaseDlg.h : header file
//

#pragma once


// CConvertDatabaseDlg dialog
class CConvertDatabaseDlg : public CDialog
{
// Construction
public:
	CConvertDatabaseDlg(CWnd* pParent = NULL);	// standard constructor
	
	BOOL CheckFileIsAccess(const TCHAR* strFullPath);
// Dialog Data
	enum { IDD = IDD_CONVERTDATABASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	void AddApplicationName();
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
	afx_msg void OnBnClickedBtnConvert();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnCbnSelchangeCbApplication();
	afx_msg void OnEnChangeEdtPassmysql();
	afx_msg void OnBnClickedBtnClose();
};
