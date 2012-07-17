
// RecursivelyRemoveFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RecursivelyRemoveFolder.h"
#include "RecursivelyRemoveFolderDlg.h"
#include "RemoveFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRecursivelyRemoveFolderDlg dialog




CRecursivelyRemoveFolderDlg::CRecursivelyRemoveFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecursivelyRemoveFolderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRecursivelyRemoveFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRecursivelyRemoveFolderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_BROWSEFOLDER, &CRecursivelyRemoveFolderDlg::OnBnClickedBtnBrowsefolder)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &CRecursivelyRemoveFolderDlg::OnBnClickedBtnRemove)
END_MESSAGE_MAP()


// CRecursivelyRemoveFolderDlg message handlers

BOOL CRecursivelyRemoveFolderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_edtFolder = (CEdit*)GetDlgItem(IDC_EDIT_FOLDER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecursivelyRemoveFolderDlg::OnPaint()
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
HCURSOR CRecursivelyRemoveFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRecursivelyRemoveFolderDlg::OnBnClickedBtnBrowsefolder()
{
	BROWSEINFO browseInfo;
	ZeroMemory(&browseInfo, sizeof(BROWSEINFO));

	TCHAR strTitle[] = _T("Choosing a folder to save your file");
	browseInfo.lpszTitle = strTitle;

	LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&browseInfo);

	if (NULL != pItemIDList) {

		TCHAR strPATH[MAX_PATH] = {0};

		if (FALSE != ::SHGetPathFromIDList(pItemIDList, strPATH)) {
			m_edtFolder->SetWindowText(strPATH);
		}

		::CoTaskMemFree(pItemIDList);
	}
}

void CRecursivelyRemoveFolderDlg::OnBnClickedBtnRemove()
{
	if (0 == m_edtFolder->GetWindowTextLength()) {
		AfxMessageBox(_T("Please enter the folder address"), MB_ICONSTOP);
	} else {

		TCHAR strPath[MAX_PATH] = {0};
		m_edtFolder->GetWindowText(strPath, MAX_PATH);

		if (TRUE == RemoveFolder(strPath)) {
			AfxMessageBox(_T("OK"), MB_ICONINFORMATION);
		} else {
			AfxMessageBox(_T("Fail"), MB_ICONSTOP);
		}
	}
}
