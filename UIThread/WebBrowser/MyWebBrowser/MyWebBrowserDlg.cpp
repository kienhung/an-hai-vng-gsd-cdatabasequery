
// MyWebBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyWebBrowser.h"
#include "MyWebBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyWebBrowserDlg dialog




CMyWebBrowserDlg::CMyWebBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyWebBrowserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyWebBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_explorer);
}

BEGIN_MESSAGE_MAP(CMyWebBrowserDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMyWebBrowserDlg message handlers

BOOL CMyWebBrowserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//ShowWindow(SW_HIDE);
	m_explorer.Navigate(L"asus.com", NULL, NULL, NULL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyWebBrowserDlg::OnPaint()
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
HCURSOR CMyWebBrowserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMyWebBrowserDlg, CDialog)

ON_EVENT(CMyWebBrowserDlg, IDC_EXPLORER1, 104, CMyWebBrowserDlg::DownloadCompleteExplorer1, VTS_NONE)
END_EVENTSINK_MAP()



void CMyWebBrowserDlg::DownloadCompleteExplorer1()
{
	::OutputDebugStringA("Down xong");
	ShowWindow(SW_SHOW);
}
