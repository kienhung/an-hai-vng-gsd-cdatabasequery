
// GetListFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetListFile.h"
#include "GetListFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGetListFileDlg dialog




CGetListFileDlg::CGetListFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetListFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetListFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDT_FOLDERPATH, m_strFolderPath);
	DDV_MaxChars(pDX, m_strFolderPath, MAX_PATH);
}

BEGIN_MESSAGE_MAP(CGetListFileDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CGetListFileDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_DUYET, &CGetListFileDlg::OnBnClickedBtnDuyet)
	ON_BN_CLICKED(IDC_BTN_WRITETOFILE, &CGetListFileDlg::OnBnClickedBtnWritetofile)
END_MESSAGE_MAP()


// CGetListFileDlg message handlers

BOOL CGetListFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetListFileDlg::OnPaint()
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
HCURSOR CGetListFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetListFileDlg::OnBnClickedBtnBrowse()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO browseInfo;
	ZeroMemory(&browseInfo, sizeof(BROWSEINFO));

	TCHAR strTitle[] = _T("Choosing a folder to save your file");
	browseInfo.lpszTitle = strTitle;

	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&browseInfo);

	if (NULL != pItemIDList) {

		TCHAR strPATH[MAX_PATH] = {0};
		if (FALSE != SHGetPathFromIDList(pItemIDList, strPATH)) {

			m_strFolderPath = strPATH;
			UpdateData(FALSE);
		}

		::CoTaskMemFree(pItemIDList);
	}

}

void CGetListFileDlg::OnBnClickedBtnDuyet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_DuyetFile.ApproveFolderToList(m_strFolderPath + _T("\\*"));
	return;
}

void CGetListFileDlg::OnBnClickedBtnWritetofile()
{
	// TODO: Add your control notification handler code here
	m_DuyetFile.WriteToFile();
}
