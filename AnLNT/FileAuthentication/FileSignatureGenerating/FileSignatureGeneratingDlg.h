
// FileSignatureGeneratingDlg.h : header file
//

#pragma once


// CFileSignatureGeneratingDlg dialog
class CFileSignatureGeneratingDlg : public CDialog
{
// Construction
public:
    CFileSignatureGeneratingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_FILESIGNATUREGENERATING_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGenerate();
    afx_msg void OnBnClickedBtnOpenfiledlg();
};
