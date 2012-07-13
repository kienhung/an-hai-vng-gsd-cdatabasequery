#pragma once
#include "NhanVien.h"
#include "map"
using namespace std;

// CThemDlg dialog

class CThemDlg : public CDialog
{
	DECLARE_DYNAMIC(CThemDlg)

public:
	CThemDlg(NHANVIEN* nhanVien = NULL, CWnd* pParent = NULL);   // standard constructor
	virtual ~CThemDlg();

// Dialog Data
	enum { IDD = IDD_THEM_DIALOG };
	CComboBox m_cbbPhongBan;
	CComboBox m_cbbGioiTinh;
	CButton m_btnOK;
	CString m_strTenNhanVien;
	CString m_strPhongBan;
	CString m_strGioiTinh;
	CString m_strSoDienThoai;
	CString m_strDiaChi;
	
	list<PHONGBAN> m_listPhongBan;
	bool m_bIsEdit;
	int m_iMaNhanVien;
protected:
	NHANVIEN InitNhanVien();
	void AddNhanVien();
	void UpdateNhanVien();
	int GetMaPhongBan();
	void GetAllListPhongBan();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
