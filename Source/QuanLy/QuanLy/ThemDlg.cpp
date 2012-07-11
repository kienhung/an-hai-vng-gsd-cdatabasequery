// ThemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuanLy.h"
#include "ThemDlg.h"


// CThemDlg dialog

IMPLEMENT_DYNAMIC(CThemDlg, CDialog)

CThemDlg::CThemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThemDlg::IDD, pParent)
{

}

CThemDlg::~CThemDlg()
{
}

void CThemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDT_HOTEN, m_strTenNhanVien);
	DDV_MaxChars(pDX, m_strTenNhanVien, MAX_NAME);

	DDX_Text(pDX, IDC_CB_PHONGBAN, m_strPhongBan);
	DDV_MaxChars(pDX, m_strPhongBan, MAX_NAME);

	DDX_Text(pDX, IDC_CB_GIOITINH, m_strGioiTinh);
	DDV_MaxChars(pDX, m_strGioiTinh, 3);

	DDX_Text(pDX, IDC_EDT_SODIENTHOAI, m_strSoDienThoai);
	DDV_MaxChars(pDX, m_strSoDienThoai, MAX_PHONE);

	DDX_Text(pDX, IDC_EDT_DIACHI, m_strDiaChi);
	DDV_MaxChars(pDX, m_strDiaChi, MAX_ADDRESS);

}


BEGIN_MESSAGE_MAP(CThemDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CThemDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CThemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}
// CThemDlg message handlers

void CThemDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CMySqlNhanVienDAO NhanVienDAO("","","","");
	
	NhanVienDAO.AddNhanVien(InitNhanVien());
}
NHANVIEN CThemDlg::InitNhanVien()
{
	UpdateData(TRUE);
	NHANVIEN nhanVien;
	_tcscpy(nhanVien.strTenNhanVien, m_strTenNhanVien);
	_tcscpy(nhanVien.strTenPhongBan, m_strPhongBan);
	_tcscpy(nhanVien.strSoDienThoai, m_strSoDienThoai);
	_tcscpy(nhanVien.strDiaChi, m_strDiaChi);
	if(m_strGioiTinh == _T("Name"))
	{

	}
	return nhanVien;
}
