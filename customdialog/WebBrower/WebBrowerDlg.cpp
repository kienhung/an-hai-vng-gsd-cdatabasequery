
// WebBrowerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrower.h"
#include "WebBrowerDlg.h"

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


// CWebBrowerDlg dialog




CWebBrowerDlg::CWebBrowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebBrowerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebBrowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_IE_WEBBROWER, m_WebBrower);

	DDX_Control(pDX, IDC_EXPLORER3, m_Ie2);
	DDX_Control(pDX, IDC_GROUP, m_Group);
}

BEGIN_MESSAGE_MAP(CWebBrowerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOAD, &CWebBrowerDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CWebBrowerDlg message handlers

BOOL CWebBrowerDlg::OnInitDialog()
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
	//m_WebBrower.Navigate(_T("google.com"), NULL, NULL, NULL, NULL);
	//m_WebBrower.SetParent(NULL);

	CCustomGroupBox* pControl = (CCustomGroupBox*)GetDlgItem (IDC_GROUP);
	HWND hwndControl = pControl->m_hWnd;
	////m_WebBrower.SetParent(pControl);
	
	CIe_WebBrower* temp = (CIe_WebBrower*)GetDlgItem(IDC_IE_WEBBROWER);
	temp->SetParent(pControl);
	pControl->SetWebBrowser(temp);
	
	m_hThread1 = CreateThread(NULL, 0, ThreadLoadWebPageFromOtherControl, pControl, 0, NULL);

	//m_hThread2 = CreateThread( NULL, 0, ThreadLoadWebPage, &m_Ie2, 0, NULL);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWebBrowerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWebBrowerDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebBrowerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWebBrowerDlg::OnBnClickedBtnLoad()
{
	// TODO: Add your control notification handler code here
	CString strURL;
	// get the new web page from the edit control
	GetDlgItemText(IDC_EDT_URL, strURL);
	// browse to it
	//m_WebBrower.Navigate(strURL, NULL, NULL, NULL, NULL);
}

DWORD WINAPI CWebBrowerDlg::ThreadLoadWebPage( LPVOID lpParam )
{
	CIe_WebBrower* e = (CIe_WebBrower*)lpParam;
	e->Navigate(_T("http://www.asus.com/"), NULL, NULL, NULL, NULL);
	return 0;
}
DWORD WINAPI CWebBrowerDlg::ThreadLoadWebPageFromOtherControl( LPVOID lpParam )
{
	CCustomGroupBox* pControl = (CCustomGroupBox*)lpParam;
	pControl->LoadWeb();
	return 0;
}