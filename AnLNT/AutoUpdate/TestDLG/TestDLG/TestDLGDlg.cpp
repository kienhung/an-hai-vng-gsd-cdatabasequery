
// TestDLGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDLG.h"
#include "TestDLGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDLGDlg dialog




CTestDLGDlg::CTestDLGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDLGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDLGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDLGDlg, CDialog)
//	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CTestDLGDlg::OnBnClickedBtnLogin)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDLGDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTestDLGDlg message handlers

BOOL CTestDLGDlg::OnInitDialog()
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

//void CTestDLGDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // device context for painting
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// Center icon in client rectangle
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// Draw the icon
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialog::OnPaint();
//	}
//}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDLGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDLGDlg::OnBnClickedBtnLogin()
{

	CString strUserName;
	CString strPassword;

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	pEdit->GetWindowText(strUserName);

	pEdit = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
	pEdit->GetWindowText(strPassword);

	CString strText;
	strText.Format(L"Username : %s. Password: %s", strUserName, strPassword);

	AfxMessageBox(strText);
}

void CTestDLGDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	::FillRect(dc.m_hDC, &rect, (HBRUSH)::GetStockObject(BLACK_BRUSH));
}

void CTestDLGDlg::OnBnClickedButton2()
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
			//::SendMessage()
			pButton->PostMessage(BM_CLICK);
			//pButton->SendMessage(BM_CLICK);
		}
		//ASSERT(pButton);
	}
}
