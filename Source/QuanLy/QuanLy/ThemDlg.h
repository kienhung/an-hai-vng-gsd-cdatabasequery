#pragma once
#include "NhanVien.h"


// CThemDlg dialog

class CThemDlg : public CDialog
{
	DECLARE_DYNAMIC(CThemDlg)

public:
	CThemDlg(NHANVIEN* nhanVien = NULL, CWnd* pParent = NULL);   // standard constructor
	virtual ~CThemDlg();

// Dialog Data
	enum { IDD = IDD_THEM_DIALOG };
	
	CString m_strTenNhanVien;
	CString m_strPhongBan;
	CString m_strGioiTinh;
	CString m_strSoDienThoai;
	CString m_strDiaChi;
	bool m_bIsEdit;
	int m_iMaNhanVien;
protected:
	NHANVIEN InitNhanVien();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
