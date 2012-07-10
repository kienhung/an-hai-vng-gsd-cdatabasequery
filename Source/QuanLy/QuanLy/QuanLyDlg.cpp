
// QuanLyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuanLy.h"
#include "QuanLyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


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
END_MESSAGE_MAP()


// CQuanLyDlg message handlers

BOOL CQuanLyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	
	InitListCtrlCols();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQuanLyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
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

	m_lstNhanVien.InsertColumn(0, _T("Tên nhân viên"), LVCFMT_LEFT, nColInterval*1.5);
	m_lstNhanVien.InsertColumn(1, _T("Phòng ban"), LVCFMT_LEFT, nColInterval*1.5);
	m_lstNhanVien.InsertColumn(2, _T("Giới tính"), LVCFMT_LEFT, nColInterval);
	m_lstNhanVien.InsertColumn(3, _T("Số điện thoại"), LVCFMT_LEFT, nColInterval);
	m_lstNhanVien.InsertColumn(4, _T("Địa chỉ"), LVCFMT_LEFT, nColInterval);
	
	m_lstNhanVien.ModifyStyle(0, LVS_REPORT | LVS_EX_GRIDLINES);
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
}

void CQuanLyDlg::OnBnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
}
