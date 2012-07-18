
// GetListFileDlg.h : header file
//

#pragma once
#include "DuyetFile.h"

// CGetListFileDlg dialog
class CGetListFileDlg : public CDialog
{
// Construction
public:
	CGetListFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GETLISTFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CString m_strFolderPath;
	CDuyetFile m_DuyetFile;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnDuyet();
};
