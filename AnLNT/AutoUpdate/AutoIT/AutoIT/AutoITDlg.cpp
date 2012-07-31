
// AutoITDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoIT.h"
#include "AutoITDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoITDlg dialog




CAutoITDlg::CAutoITDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoITDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoITDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAutoITDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoITDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAutoITDlg message handlers

BOOL CAutoITDlg::OnInitDialog()
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

void CAutoITDlg::OnPaint()
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
HCURSOR CAutoITDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAutoITDlg::OnBnClickedButton1()
{
	CString strClassName = L"#32770";
	CString strWndName = L"TestDLG";

	int iEdtUserNameID = 0x000003E9;
	int iEdtPasswordID = 0x00003EA;
	int iBtnLogin = 0x000003E8;

	CWnd *pWnd = CWnd::FindWindow(strClassName, strWndName);
	if (pWnd != NULL) {

		CEdit * pEdit = (CEdit*)pWnd->GetDlgItem(iEdtUserNameID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"AnLNT");
		}

		pEdit = (CEdit *)pWnd->GetDlgItem(iEdtPasswordID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"123456");
		}

		CButton *pButton = (CButton*)GetDlgItem(iBtnLogin);
		if (NULL != pButton) {
			//pWnd->SendMessage(WM_ACTIVATE, 1);
			::SetActiveWindow(pWnd->m_hWnd);
			pButton->SendMessage(BM_CLICK);
		}
	}


	//pWnd->PostMessage(WM_QUIT);


	//TRACE("%d", hwnd);
	ASSERT(pWnd);

}
