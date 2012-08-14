
// ConvertDatabaseDlg.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "ConvertDatabase.h"
#include "ConvertDatabaseDlg.h"
#include "ConvertDB.h"
#include "Strsafe.h"
#include "StringConverter.h"
#include "AccessConvertDB.h"
#include "MySQLConvertDB.h"

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
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CConvertDatabaseDlg::OnBnClickedBtnBrowse)
	ON_CBN_SELCHANGE(IDC_CB_APPLICATION, &CConvertDatabaseDlg::OnCbnSelchangeCbApplication)
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
	AddApplicationName();
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

void CConvertDatabaseDlg::AddApplicationName()
{
	CComboBox* cb_Application = (CComboBox*)GetDlgItem(IDC_CB_APPLICATION);
	cb_Application->AddString(_T("NetCafe"));
	cb_Application->AddString(_T("OneNet"));
	
	cb_Application->SetCurSel(0);
}

void CConvertDatabaseDlg::OnBnClickedBtnConvert()
{
	TCHAR strPassword[150] = {0};
	GetDlgItemText(IDC_EDT_PASSMYSQL, strPassword, 150);

	CConvertDB* converter;
	

	TCHAR strAppName[100] = {0};
	GetDlgItemText(IDC_CB_APPLICATION, strAppName, 100);

	if(wcscmp(strAppName, _T("OneNet")) == 0)
	{
		converter = new CMySQLConvertDB;
		converter->SetPasswordMySQL(strPassword);
		if(converter->Convert(_T("")))
		{
			AfxMessageBox(_T("Convert succeed"), MB_ICONINFORMATION);
		}
		return;
	}




	TCHAR strPath[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDT_PATH, strPath, MAX_PATH);
	
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile(strPath, &findData);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("File is not exist"), MB_ICONSTOP);
		return;
	}
	
	CString strExtension = findData.cFileName;
	strExtension.Delete(0, strExtension.ReverseFind(L'.') + 1);
	
	

	
	if(wcscmp(strAppName, _T("NetCafe")) == 0)
	{
		if(!(wcscmp(strExtension, _T("mdb")) == 0 || wcscmp(strExtension, _T("accdb")) == 0))
		{
			AfxMessageBox(_T("File is invalid"), MB_ICONSTOP);
			return;
		}
		converter = new CAccessConvertDB;
		converter->SetPasswordMySQL(strPassword);
	}
	 
	if(converter->Convert(strPath))
	{
		AfxMessageBox(_T("Convert succeed"), MB_ICONINFORMATION);
	}

}
//MASOTHUY0101148362
void CConvertDatabaseDlg::OnBnClickedBtnBrowse()
{
	CString strExtension = _T("");

	TCHAR strApplicationName[100] = {0};
	GetDlgItemText(IDC_CB_APPLICATION, strApplicationName, 100);

	if(wcscmp(strApplicationName, _T("NetCafe")) == 0)
	{
		strExtension = _T("MS Access Databases(*.mdb, *.accdb)|*.mdb;*.accdb||");
	}

	CFileDialog fileDialog(TRUE, NULL,NULL, OFN_NOVALIDATE|OFN_OVERWRITEPROMPT,strExtension  );
	
	if(fileDialog.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDT_PATH, fileDialog.GetPathName());
	}
}

void CConvertDatabaseDlg::OnCbnSelchangeCbApplication()
{
	TCHAR strAppName[100] = {0};
	GetDlgItemText(IDC_CB_APPLICATION, strAppName, 100);
	if(wcscmp(strAppName, _T("OneNet")) == 0)
	{
		::EnableWindow(GetDlgItem(IDC_EDT_PATH)->m_hWnd, FALSE);
		::EnableWindow(GetDlgItem(IDC_BTN_BROWSE)->m_hWnd, FALSE);
	}
	else
	{
		::EnableWindow(GetDlgItem(IDC_EDT_PATH)->m_hWnd, TRUE);
		::EnableWindow(GetDlgItem(IDC_BTN_BROWSE)->m_hWnd, TRUE);
	}
}
