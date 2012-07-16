
// HttpDownloaderAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HttpDownloaderApp.h"
#include "HttpDownloaderAppDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment (lib, "lib/Downloader")

// CHttpDownloaderAppDlg dialog




CHttpDownloaderAppDlg::CHttpDownloaderAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHttpDownloaderAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpDownloaderAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpDownloaderAppDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_BROWSEFOLDER, &CHttpDownloaderAppDlg::OnBnClickedBtnBrowsefolder)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CHttpDownloaderAppDlg::OnBnClickedBtnDownload)
END_MESSAGE_MAP()


// CHttpDownloaderAppDlg message handlers

BOOL CHttpDownloaderAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_httpDownloader = new CHttpDownloader();
	
	m_edtURL = (CEdit*)GetDlgItem(IDC_EDIT_URL);
	m_edtURL->SetLimitText(MAX_URL_LENGTH - 1);
	m_edtURL->SetWindowText(_T("google.com.vn"));

	m_edtFileName = (CEdit*)GetDlgItem(IDC_EDIT_FILENAME);
	m_edtFileName->SetLimitText(MAX_FILE_NAME - 1);
	m_edtFileName->SetWindowText(_T("index.html"));

	m_edtOutput = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);

	TCHAR strOutput[MAX_PATH] = {0};
	if (S_OK == ::SHGetFolderPath(m_hWnd, CSIDL_COMMON_DESKTOPDIRECTORY, NULL, SHGFP_TYPE_CURRENT,  strOutput)) {
		m_edtOutput->SetWindowText(strOutput);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CHttpDownloaderAppDlg::OnPaint()
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
HCURSOR CHttpDownloaderAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHttpDownloaderAppDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if (m_httpDownloader != NULL) {
		delete m_httpDownloader;
	}
	// TODO: Add your message handler code here
}

void CHttpDownloaderAppDlg::OnBnClickedBtnBrowsefolder()
{
	BROWSEINFO browseInfo;
	ZeroMemory(&browseInfo, sizeof(BROWSEINFO));

	TCHAR strTitle[] = _T("Choosing a folder to save your file");
	browseInfo.lpszTitle = strTitle;

	LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&browseInfo);

	if (NULL != pItemIDList) {

		TCHAR strPATH[MAX_PATH] = {0};

		if (FALSE != ::SHGetPathFromIDList(pItemIDList, strPATH)) {
			m_edtOutput->SetWindowText(strPATH);
		}

		::CoTaskMemFree(pItemIDList);
	}
	
}

void CHttpDownloaderAppDlg::OnBnClickedBtnDownload()
{

	try {
		CString strBuffer;

		m_edtURL->GetWindowText(strBuffer);
		strBuffer.Trim();
		if (0 == strBuffer.GetLength()) {
			throw _T("Please enter URL");
		}
		m_httpDownloader->SetURL(strBuffer.GetBuffer());

		m_edtFileName->GetWindowText(strBuffer);
		strBuffer.Trim();
		if (0 == strBuffer.GetLength()) {
			throw _T("Please enter file name");
		}
		m_httpDownloader->SetFileName(strBuffer.GetBuffer());

		m_edtOutput->GetWindowText(strBuffer);
		m_httpDownloader->SetSavingFolderPath(strBuffer.GetBuffer());

		if (m_httpDownloader->DownLoad()) {
			AfxMessageBox(_T("Download sucessfully"), MB_ICONINFORMATION);
		} else {
			AfxMessageBox(_T("File not found"), MB_ICONSTOP);
		}

	} catch (CInternetException * pInternetException) {

		const int MAX_LENGTH = 255;
		TCHAR strMessage[MAX_LENGTH];
	
		pInternetException->GetErrorMessage(strMessage, MAX_LENGTH);
		AfxMessageBox(strMessage, MB_ICONSTOP);

		pInternetException->Delete();
	} catch (const TCHAR strErrorMessage[]) {
		AfxMessageBox(strErrorMessage, MB_ICONSTOP);
	}

}
