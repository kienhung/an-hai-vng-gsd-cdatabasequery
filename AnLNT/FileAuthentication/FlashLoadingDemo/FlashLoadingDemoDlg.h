
// FlashLoadingDemoDlg.h : header file
//

#pragma once
#include "shockwaveflash.h"


// CFlashLoadingDemoDlg dialog
class CFlashLoadingDemoDlg : public CDialog
{
// Construction
public:
    CFlashLoadingDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_FLASHLOADINGDEMO_DIALOG };

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
    afx_msg void OnBnClickedBtnOpenfiledlg();
private:
    CShockwaveflash m_shockwaveFlash;
public:
    afx_msg void OnBnClickedBtnLoad();
};
