
// ListControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListControl.h"
#include "ListControlDlg.h"

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


// CListControlDlg dialog




CListControlDlg::CListControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CListControlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CListControlDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_ICON, &CListControlDlg::OnBnClickedBtnIcon)
	ON_BN_CLICKED(IDC_BTN_SMALLICON, &CListControlDlg::OnBnClickedBtnSmallicon)
	ON_BN_CLICKED(IDC_BTN_LIST, &CListControlDlg::OnBnClickedBtnList)
	ON_BN_CLICKED(IDC_BTN_REPORT, &CListControlDlg::OnBnClickedBtnReport)
END_MESSAGE_MAP()


// CListControlDlg message handlers

BOOL CListControlDlg::OnInitDialog()
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

	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST);

	LVCOLUMN lvColumn;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 120;
	lvColumn.pszText = L"Full Name";
	m_pListCtrl->InsertColumn(0, &lvColumn);
	
	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = L"Profession";
	m_pListCtrl->InsertColumn(1, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 80;
	lvColumn.pszText = L"Fav Sport";
	m_pListCtrl->InsertColumn(2, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 75;
	lvColumn.pszText = L"Hobby";
	m_pListCtrl->InsertColumn(3, &lvColumn);

	
	LVITEM lvItem;
	int nItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Sandra C. Anschwitz";
	nItem = m_pListCtrl->InsertItem(&lvItem);

	m_pListCtrl->SetItemText(nItem, 1, L"Single");
	m_pListCtrl->SetItemText(nItem, 2, L"Hand Ball");
	m_pListCtrl->SetItemText(nItem, 3, L"Beach");

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 1;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Roger A.Muller";
	nItem = m_pListCtrl->InsertItem(&lvItem);

	m_pListCtrl->SetItemText(nItem, 1, L"Footballer");
	m_pListCtrl->SetItemText(nItem, 2, L"Tennis");
	m_pListCtrl->SetItemText(nItem, 3, L"Teaching");

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 2;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Marie-Julie W. Gross";
	nItem = m_pListCtrl->InsertItem(&lvItem);

	m_pListCtrl->SetItemText(nItem, 1, L"Student");
	m_pListCtrl->SetItemText(nItem, 2, L"Boxing");
	m_pListCtrl->SetItemText(nItem, 3, L"Programming");


	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 3;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Ella Pius Roger";
	nItem = m_pListCtrl->InsertItem(&lvItem);

	m_pListCtrl->SetItemText(nItem, 1, L"Architect");
	m_pListCtrl->SetItemText(nItem, 2, L"Ping-pong");
	m_pListCtrl->SetItemText(nItem, 3, L"Songo");

	/*
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Sandra C. Anschwitz";

	m_pListCtrl->InsertItem(&lvItem);
	
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 1;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Roger A.Muller";

	m_pListCtrl->InsertItem(&lvItem);

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 2;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Marie-Julie W. Gross";

	m_pListCtrl->InsertItem(&lvItem);

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 3;
	lvItem.iSubItem = 0;
	lvItem.pszText = L"Ella Pius Roger";

	m_pListCtrl->InsertItem(&lvItem);

	*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListControlDlg::OnPaint()
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


HCURSOR CListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CListControlDlg::OnBnClickedBtnClose()
{
	DestroyWindow();
}

void CListControlDlg::OnBnClickedBtnIcon()
{
	m_pListCtrl->SetView(LV_VIEW_ICON);
}

void CListControlDlg::OnBnClickedBtnSmallicon()
{
	m_pListCtrl->SetView(LV_VIEW_SMALLICON);
}

void CListControlDlg::OnBnClickedBtnList()
{
	m_pListCtrl->SetView(LV_VIEW_LIST);
}

void CListControlDlg::OnBnClickedBtnReport()
{
	m_pListCtrl->SetView(LV_VIEW_DETAILS);
}
