
// ConvertDatabaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertDatabase.h"
#include "ConvertDatabaseDlg.h"
#include "ConvertDB.h"
#include "Strsafe.h"
#include "MakeWindowTransparent.h"
#include "StringConverter.h"


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


// CConvertDatabaseDlg dialog




CConvertDatabaseDlg::CConvertDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertDatabaseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvertDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvertDatabaseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CONVERT, &CConvertDatabaseDlg::OnBnClickedBtnConvert)
END_MESSAGE_MAP()


// CConvertDatabaseDlg message handlers

BOOL CConvertDatabaseDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConvertDatabaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConvertDatabaseDlg::OnPaint()
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
HCURSOR CConvertDatabaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CConvertDatabaseDlg::OnBnClickedBtnConvert()
{

	CStringConverter stringConvert;
	CString strPath;
	GetDlgItemText(IDC_EDT_PATH, strPath.GetBuffer(), MAX_PATH);

	//Write to text file
	TCHAR strFileName[MAX_PATH] = {0};
	GetCurrentDirectory(MAX_PATH, strFileName);

	StringCchPrintf(strFileName, MAX_PATH, _T("%s\\pass.txt"), strFileName);
	
	char strFileNameTemp[MAX_PATH] = {0};
	for(int i = 0 ; i < (int)wcslen(strFileName); i++)
	{
		strFileNameTemp[i] = strFileName[i];
	}
	
	
	
	FILE *pFile;
	
	pFile = fopen(strFileNameTemp , "w");
	if(pFile == NULL)
	{
		return;
	}

	wmemset(strFileName, 0, MAX_PATH);
	StringCchPrintf(strFileName, MAX_PATH, _T("%s"), strPath.GetBuffer());
	
	for(int i = 0 ; i < (int)wcslen(strFileName); i++)
	{
		strFileNameTemp[i] = strFileName[i];
	}

	fputs( strFileNameTemp, pFile);
	fclose(pFile);

	STARTUPINFOW siStartupInfo; 
    PROCESS_INFORMATION piProcessInfo; 
    memset(&siStartupInfo, 0, sizeof(siStartupInfo)); 
    memset(&piProcessInfo, 0, sizeof(piProcessInfo)); 
    siStartupInfo.cb = sizeof(siStartupInfo);

	DWORD dwExitCode = 0; 
	TCHAR strCurrentPath[MAX_PATH] = {0};
	//CString strCurrentPath = _T("");
	
	GetCurrentDirectory(MAX_PATH, strCurrentPath);
	StringCchPrintf(strCurrentPath, MAX_PATH, _T("%s\\PasswordViewer.exe"), strCurrentPath);
	//strCurrentPath.Append(_T("\\accesspv.exe"));
	if(::CreateProcess(strCurrentPath, NULL,  NULL, NULL, false, 0, NULL,NULL,&siStartupInfo,&piProcessInfo))
	{
		Sleep(100);

	}

	
	strPath = _T("C:\\Program Files\\Netcafe Server\\database\\netcafe9.mdb");
	CConvertDB converter;
	converter.Convert(strPath);
	
}
//MASOTHUY0101148362

