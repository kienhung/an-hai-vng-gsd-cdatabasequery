
// FullCreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FullCreen.h"
#include "FullCreenDlg.h"

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


// CFullCreenDlg dialog




CFullCreenDlg::CFullCreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullCreenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFullCreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFullCreenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_FULLCREEN, &CFullCreenDlg::OnBnClickedBtnFullcreen)
	ON_BN_CLICKED(IDC_BTN_NORMAL, &CFullCreenDlg::OnBnClickedBtnNormal)
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFullCreenDlg message handlers

BOOL CFullCreenDlg::OnInitDialog()
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
	SetTimer(1, 500,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFullCreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFullCreenDlg::OnPaint()
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
HCURSOR CFullCreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFullCreenDlg::OnBnClickedBtnFullcreen()
{
	// TODO: Add your control notification handler code here
	/*HDC hDC = ::GetWindowDC(NULL); 
	CWnd* handle = GetWindow( IDD_FULLCREEN_DIALOG);

	SetWindowPos(handle, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_SHOWWINDOW);*/

	int  iCX,iCY; 
    iCX = GetSystemMetrics(SM_CXSCREEN);
    iCY = GetSystemMetrics(SM_CYSCREEN);
     
	DWORD style =  GetStyle();
	style &= ~WS_BORDER;
	this->ModifyStyle(WS_BORDER, NULL, 0);
    //SetWindowPos(&wndTopMost, 0, 0, iCX, iCY, SWP_NOSIZE| SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	ShowWindow(SW_SHOWMAXIMIZED);
}

void CFullCreenDlg::OnBnClickedBtnNormal()
{
	// TODO: Add your control notification handler code here
	//KillTimer(1);
	this->ModifyStyle(NULL, WS_BORDER, 0);
	ShowWindow(SW_SHOWNORMAL);
}
void CFullCreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		CWnd* winMain = GetWindow( IDD_FULLCREEN_DIALOG);
		CWnd* winForeground = GetForegroundWindow();
		this->ModifyStyleEx(NULL, WS_EX_TOPMOST , 0);
		if(winMain != winForeground)
		{
			//ShowWindow(SW_SHOW);
			//this->ModifyStyle(WS_BORDER, NULL, 0);
			//ShowWindow(SW_SHOWMAXIMIZED);
			
			HWND hFrgWnd = ::GetForegroundWindow();
			//SetForegroundWindow();
			//::GetForegroundWindow();
			AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
			BOOL flag = FALSE;
			do
			{

				flag = ::SetForegroundWindow(GetSafeHwnd());
				//if(flag)
				//flag = this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			}while(!flag);

			AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
			BringWindowToTop();
			
		}

		/*HWND hFrgWnd = ::GetForegroundWindow();
		AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
		::SetForegroundWindow(GetSafeHwnd());
		AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);*/
	}
}
void CFullCreenDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
	//if(nIDEvent == 1)
	//{
	//	CWnd* winMain = GetWindow( IDD_FULLCREEN_DIALOG);
	//	CWnd* winForeground = GetForegroundWindow();
	//	if(winMain != winForeground)
	//	{
	//		ShowWindow(SW_SHOW);
	//		SetForegroundWindow();
	//	}

	//	/*HWND hFrgWnd = ::GetForegroundWindow();
	//	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
	//	::SetForegroundWindow(GetSafeHwnd());
	//	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);*/
	//}
	// TODO: Add your message handler code here
	::OutputDebugString(_T("kill focus \n"));
	
}
int CFullCreenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	return CDialog::OnCreate(lpCreateStruct);
}