
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	return TRUE;  // return TRUE  unless you set the focus to a control
}



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
	int iBtnLoginID = 0x000003E8;
	int iCheckBlueID = 0x000003ED;
	//int iCheckBlue = 

	CWnd *pWnd = CWnd::FindWindow(strClassName, strWndName);
	if (pWnd != NULL) {

		pWnd->SetForegroundWindow();

		CEdit * pEdit = (CEdit*)pWnd->GetDlgItem(iEdtUserNameID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"an_an_289");
		}

		pEdit = (CEdit *)pWnd->GetDlgItem(iEdtPasswordID);
		if (NULL != pEdit) {
			pEdit->SendMessage(WM_SETTEXT, NULL, (LPARAM)L"123456654321");
		}

		CButton *pButton = (CButton*)GetDlgItem(iCheckBlueID);
		if (pButton != NULL) {
			//::PostMessage(pButton->m_hWnd, WM_LBUTTONDOWN, 0, 0);
			//::PostAppMessage(pButton->m_hWnd, BM_SETCHECK,  BST_CHECKED, 0);
			::SendMessage(pButton->m_hWnd, 0x00F1,  0, 0);
		}

		/*
		CButton *pButton = (CButton*)GetDlgItem(iBtnLoginID);

		if (NULL != pButton) {

			WORD lParam  = (WORD)pButton->m_hWnd;
			WORD wParam = MAKEWPARAM(iBtnLoginID, BN_CLICKED);

			pWnd->SendMessage(WM_COMMAND, wParam, lParam);

		}
		*/
		//pButton = (CButton *)GetDlgItem()
	}


	//pWnd->PostMessage(WM_QUIT);


	//TRACE("%d", hwnd);
	ASSERT(pWnd);

}
