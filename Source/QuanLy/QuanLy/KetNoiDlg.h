#pragma once


// CKetNoiDlg dialog

class CKetNoiDlg : public CDialog
{
	DECLARE_DYNAMIC(CKetNoiDlg)

public:
	CKetNoiDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKetNoiDlg();

// Dialog Data
	enum { IDD = IDD_KETNOI_DIALOG };
	CString m_strUsername;
	CString m_strPassword;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void UpdateConnectData();
	char* CStringToArrChar(CString cStrSource);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
