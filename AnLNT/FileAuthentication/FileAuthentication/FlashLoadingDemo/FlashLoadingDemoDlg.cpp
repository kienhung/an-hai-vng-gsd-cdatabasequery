
// FlashLoadingDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FlashLoadingDemo.h"
#include "FlashLoadingDemoDlg.h"

#include "FileSignature.h"
#pragma comment (lib, "lib/FileAuthentication.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlashLoadingDemoDlg dialog




CFlashLoadingDemoDlg::CFlashLoadingDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashLoadingDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlashLoadingDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH, m_shockwaveFlash);
}

BEGIN_MESSAGE_MAP(CFlashLoadingDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPENFILEDLG, &CFlashLoadingDemoDlg::OnBnClickedBtnOpenfiledlg)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CFlashLoadingDemoDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &CFlashLoadingDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFlashLoadingDemoDlg message handlers

BOOL CFlashLoadingDemoDlg::OnInitDialog()
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

void CFlashLoadingDemoDlg::OnPaint()
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
HCURSOR CFlashLoadingDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFlashLoadingDemoDlg::OnBnClickedBtnOpenfiledlg()
{
	TCHAR strFilter[] = { L"swf Files (*.swf)|*.swf|All Files (*.*)|*.*||" };
	CFileDialog fileDlg(TRUE, L".swf", NULL, 0, strFilter);

	if (fileDlg.DoModal() == IDOK) {

		CEdit* pEdit = (CEdit*) GetDlgItem(IDC_EDT_INPUT);

		if (NULL != pEdit) {
			pEdit->SetWindowText(fileDlg.GetPathName());
		}
	}
}

void CFlashLoadingDemoDlg::OnBnClickedBtnLoad()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDT_INPUT);

	if (NULL != pEdit) {

		CString strFilePath;
		pEdit->GetWindowText(strFilePath);

		CFileSignature fileSignature;

		if (TRUE == fileSignature.VerifySignature(strFilePath)) {

			m_shockwaveFlash.put_Movie(strFilePath);

		} else {

			AfxMessageBox(L"Invalid input", MB_ICONSTOP);
		}

	}
}

void CFlashLoadingDemoDlg::OnBnClickedButton3()
{
	m_shockwaveFlash.Stop();
}
