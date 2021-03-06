
// QuanLyDlg.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "QuanLy.h"
#include "QuanLyDlg.h"
#include "MyException.h"
#include "StringConverter.h"
#pragma warning(disable: 4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQuanLyDlg dialog




CQuanLyDlg::CQuanLyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuanLyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuanLyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LST_NHANVIEN, m_lstNhanVien);
}

BEGIN_MESSAGE_MAP(CQuanLyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_Add, &CQuanLyDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_Edit, &CQuanLyDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_Delete, &CQuanLyDlg::OnBnClickedBtnDelete)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_THEM, &CQuanLyDlg::OnPopupThem)
	ON_COMMAND(ID_POPUP_XOA, &CQuanLyDlg::OnPopupXoa)
	ON_COMMAND(ID_POPUP_SUA, &CQuanLyDlg::OnPopupSua)
END_MESSAGE_MAP()


// CQuanLyDlg message handlers

BOOL CQuanLyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	const char *c = mysql_get_client_info();
	//AfxMessageBox(
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	try {
		InitListCtrlCols();
	} catch (CMyException *pException) {
		if (NULL != pException) {
			AfxMessageBox(pException->GetMessage());
		}
	}
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQuanLyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQuanLyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CQuanLyDlg::InitListCtrlCols()
{
	CRect rect;
	
	m_lstNhanVien.GetClientRect(&rect);
	int nColInterval = rect.Width()/6;

	
	
	m_lstNhanVien.InsertColumn(0, _T("Tên nhân viên"));
	m_lstNhanVien.SetColumnWidth(0, (int)(nColInterval*1.5));

	m_lstNhanVien.InsertColumn(1, _T("Phòng ban"));
	m_lstNhanVien.SetColumnWidth(1, (int)(nColInterval*1.5));

	m_lstNhanVien.InsertColumn(2, _T("Giới tính"));
	m_lstNhanVien.SetColumnWidth(2, (int)(nColInterval*0.5));

	m_lstNhanVien.InsertColumn(3, _T("Số điện thoại"));
	m_lstNhanVien.SetColumnWidth(3, nColInterval);

	m_lstNhanVien.InsertColumn(4, _T("Địa chỉ"));
	m_lstNhanVien.SetColumnWidth(4, nColInterval * 3);

	m_lstNhanVien.InsertColumn(5, _T("Mã nhân viên"));
	m_lstNhanVien.SetColumnWidth(5, 0);

	//m_lstNhanVien.ModifyStyle(0, LVS_REPORT | LVS_EX_GRIDLINES, 0);
	m_lstNhanVien.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_UNDERLINECOLD);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_WIDTH;
	
	// Double the column width of the first column.
	if (m_lstNhanVien.GetColumn(5, &col))
	{
		col.cx = 0;
		col.fmt = LVCFMT_FIXED_WIDTH;
		m_lstNhanVien.SetColumn(5, &col);
	}
	if (m_lstNhanVien.GetColumn(4, &col))
	{
		col.fmt = LVCFMT_FIXED_WIDTH;
		m_lstNhanVien.SetColumn(4, &col);
	}
	
	UpdateListNhanVien();
	
	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQuanLyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQuanLyDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CThemDlg* dlg = new CThemDlg();
	if(dlg->DoModal() == IDOK)
	{
		UpdateListNhanVien();
	}
}

void CQuanLyDlg::OnBnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
	int iIndex = -1;
	POSITION nPos = m_lstNhanVien.GetFirstSelectedItemPosition();
    if (nPos)
    {
        iIndex = m_lstNhanVien.GetNextSelectedItem(nPos);
    }
	
	if(iIndex < 0)
		return;
	m_lstNhanVien.SetItemState(iIndex,LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);

	NHANVIEN nhanVien;
	_tcscpy(nhanVien.strTenNhanVien, m_lstNhanVien.GetItemText(iIndex, 0));
	_tcscpy(nhanVien.strTenPhongBan, m_lstNhanVien.GetItemText(iIndex, 1));
	CString strGioiTinh = m_lstNhanVien.GetItemText(iIndex, 2);
	_tcscpy(nhanVien.strSoDienThoai, m_lstNhanVien.GetItemText(iIndex, 3));
	_tcscpy(nhanVien.strDiaChi, m_lstNhanVien.GetItemText(iIndex, 4));

	CString strMaNhanVien = m_lstNhanVien.GetItemText(iIndex, 5);
	nhanVien.iMaNhanVien = _wtoi(strMaNhanVien);

	if(wcscmp(strGioiTinh, _T("Nam")) == 0)
	{
		nhanVien.cGioiTinh = 1;
	}
	else
		nhanVien.cGioiTinh = 0;
	
	
	int index = m_lstNhanVien.GetNextItem(-1, LVNI_SELECTED);
	
	CThemDlg dlg(&nhanVien);
	if(dlg.DoModal() == IDOK)
	{
		UpdateListNhanVien();
	}
}

void CQuanLyDlg::UpdateListNhanVien()
{
	CQuanLyApp* pApp = static_cast <CQuanLyApp*> ( AfxGetApp());
	
	CNhanVienDAO* NhanVienDAO = new CMySqlNhanVienDAO(pApp->ConnectString.m_strUsername,
													  pApp->ConnectString.m_strPasssword, 
													  pApp->ConnectString.m_strServerAddress,
													  pApp->ConnectString.m_strDatabaseName);
	list<NHANVIEN> lstNhanVien;

	NhanVienDAO->GetAll(&lstNhanVien);
	m_lstNhanVien.DeleteAllItems();
	list<NHANVIEN>::iterator it ;

	int iIndex = 0;
	for (it = lstNhanVien.begin() ; it != lstNhanVien.end(); it++, iIndex++) 
	{
		NHANVIEN nhanVien = *it;
		InsertItemNhanVien(nhanVien, iIndex);
	}
	return;
}
void CQuanLyDlg::InsertItemNhanVien(const NHANVIEN &nhanVien, int iIndex)
{
	LVITEM lvItemNhanVien;
	lvItemNhanVien.mask = LVIF_TEXT | LVIF_STATE;
	lvItemNhanVien.state = LVIS_OVERLAYMASK;
	lvItemNhanVien.stateMask = LVIS_SELECTED;
	lvItemNhanVien.iItem = iIndex;
	
	// Insert ten nhan vien.
	lvItemNhanVien.iSubItem = 0;
	lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(nhanVien.strTenNhanVien);
	m_lstNhanVien.InsertItem(&lvItemNhanVien);

	// Insert phong ban.
	lvItemNhanVien.iSubItem = 1;
	lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(nhanVien.strTenPhongBan);
	m_lstNhanVien.SetItem(&lvItemNhanVien);

	// Insert gioi tinh.
	lvItemNhanVien.iSubItem = 2;
	if(nhanVien.cGioiTinh == 0)
		lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(_T("Nữ"));
	else
		lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(_T("Nam"));
	m_lstNhanVien.SetItem(&lvItemNhanVien);

	// Insert so dien thoai.
	lvItemNhanVien.iSubItem = 3;
	lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(nhanVien.strSoDienThoai);
	m_lstNhanVien.SetItem(&lvItemNhanVien);

	// Insert dia chi.
	lvItemNhanVien.iSubItem = 4;
	lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)(nhanVien.strDiaChi);
	m_lstNhanVien.SetItem(&lvItemNhanVien);

	// Insert ma nhan vien.
	char strMaNhanVien[33];
	itoa(nhanVien.iMaNhanVien, strMaNhanVien, 10);
	CStringConverter Convert;
	lvItemNhanVien.iSubItem = 5;
	lvItemNhanVien.pszText = (LPTSTR)(LPCTSTR)( Convert.UTF8ToUnicode(&strMaNhanVien[0]));
	m_lstNhanVien.SetItem(&lvItemNhanVien);
}
void CQuanLyDlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	int iIndex = m_lstNhanVien.GetNextItem(-2, LVNI_SELECTED);
	if(iIndex < 0)
		return;
	CString strMaNhanVien = m_lstNhanVien.GetItemText(iIndex, 5);
	int iMaNhanVien = _wtoi(strMaNhanVien);
	CQuanLyApp* pApp = static_cast <CQuanLyApp*> ( AfxGetApp());
	try
	{
		CMySqlNhanVienDAO nhanVienDAO(pApp->ConnectString.m_strUsername,
									  pApp->ConnectString.m_strPasssword, 
									  pApp->ConnectString.m_strServerAddress,
									  pApp->ConnectString.m_strDatabaseName);
		if(nhanVienDAO.DeleteNhanVien(iMaNhanVien))
		{
			UpdateListNhanVien();
		}
	}catch (CMyException *pException) {
		if (NULL != pException) {
			AfxMessageBox(pException->GetMessage());
		}
	}
}

void CQuanLyDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here
	CMenu mnuPopupListNhanVien;
	mnuPopupListNhanVien.LoadMenu(IDR_MENU_LIST_NHANVIEN);
	CRect rectListControl;
	m_lstNhanVien.GetWindowRect(&rectListControl);

	CMenu *mnuPopupMenu = mnuPopupListNhanVien.GetSubMenu(0);
	ASSERT(mnuPopupMenu);
	if( rectListControl.PtInRect(point) )
	{
		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CQuanLyDlg::OnPopupThem()
{
	// TODO: Add your command handler code here
	OnBnClickedBtnAdd();
}

void CQuanLyDlg::OnPopupXoa()
{
	// TODO: Add your command handler code here
	OnBnClickedBtnDelete();
}

void CQuanLyDlg::OnPopupSua()
{
	// TODO: Add your command handler code here
	OnBnClickedBtnEdit();
}
