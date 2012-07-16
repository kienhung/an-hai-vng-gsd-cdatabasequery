
// HttpDownloaderAppDlg.h : header file
//

#pragma once
#include "HttpDownloader.h"

// CHttpDownloaderAppDlg dialog
class CHttpDownloaderAppDlg : public CDialog
{
// Construction
public:
	CHttpDownloaderAppDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_HTTPDOWNLOADERAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CHttpDownloader *m_httpDownloader;

	CEdit *m_edtURL;
	CEdit *m_edtFileName;
	CEdit *m_edtOutput;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnBrowsefolder();
	afx_msg void OnBnClickedBtnDownload();
};
