// CSMServerSimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSMServerSimulator.h"
#include "CSMServerSimulatorDlg.h"
#include "MyDefine.h"
#include "PopupDialogThread.h"

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


// CCSMServerSimulatorDlg dialog




CCSMServerSimulatorDlg::CCSMServerSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSMServerSimulatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSMServerSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCSMServerSimulatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SOCKET, OnAsyncSocketNotify)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CCSMServerSimulatorDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_DOWN, &CCSMServerSimulatorDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_UP, &CCSMServerSimulatorDlg::OnBnClickedBtnUp)
END_MESSAGE_MAP()


// CCSMServerSimulatorDlg message handlers

BOOL CCSMServerSimulatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	g_Listener.Start(m_hWnd);

	//AfxBeginThread(RUNTIME_CLASS(CPopupDialogThread), 0, 0, 0 );

	m_bIsPopupDialogExist = m_popupDialog.Create(CPopupDlg::IDD);
	if (TRUE == m_bIsPopupDialogExist)
	{
		//m_popupDialog.ShowWindow(SW_SHOW);

		//m_popupDialog.SetWindowPos(NULL, 500, 80, 0, 0, SWP_NOSIZE);
		//SetTimer(TIMER_MOVE_POPUPDIALOG, 10, NULL);

		//RECT rect;
		//GetWindowRect(&rect);
		//GetClientRect(&rect);
		//ClientToScreen(&rect);


		RECT popupDialogWindowRect;
		m_popupDialog.GetClientRect(&popupDialogWindowRect);

		m_iWidthPopupDialog = popupDialogWindowRect.right - popupDialogWindowRect.left;
		m_iHeightPopupDialog = popupDialogWindowRect.bottom - popupDialogWindowRect.top;

		m_iStep = 0;
		m_iCurrentHeight = 0;

		m_bIsPopupDialogUping = TRUE;

		m_popupDialog.SetWindowPos(NULL, 0, 0, 0, 0, 0);
		m_popupDialog.ShowWindow(SW_SHOW);

		HANDLE hThread = ::CreateThread(NULL, 0, MovePopupDialogThreadFunction, this, 0, NULL);

		if (NULL != hThread) {
			::CloseHandle(hThread);
		}
		//RECT mainDialogWindowRect;
		//GetWindowRect(&mainDialogWindowRect);

		//m_iXPopupDialog = mainDialogWindowRect.right - m_iWidthPopupDialog;
		//m_iYPopupDialog = mainDialogWindowRect.bottom;
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCSMServerSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCSMServerSimulatorDlg::OnPaint()
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
HCURSOR CCSMServerSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCSMServerSimulatorDlg::OnAsyncSocketNotify(WPARAM wParam, LPARAM lParam)
{
	g_Listener.ProcessSocketMsg(wParam, lParam);
	return 1;
}

void CCSMServerSimulatorDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	g_Listener.Stop();
	// TODO: Add your message handler code here
}

void CCSMServerSimulatorDlg::OnBnClickedOk()
{
	ShowPopupDlg();
}

BOOL CCSMServerSimulatorDlg::ShowPopupDlg()
{
	if (TRUE == m_bIsPopupDialogExist)
	{

		//m_popupDialog.ShowWindow(SW_SHOW);

		//m_popupDialog.SetWindowPos(this, 500, 80, 0, 0, SWP_NOSIZE);
	}


	//AfxMessageBox(L"Show popup");

	//CPopupDlg popupDlg;

	//if (popupDlg.Create(CPopupDlg::IDD)) {
	//
	//	popupDlg.ShowWindow(SW_SHOW);

	//	MSG msg;
	//	while (GetMessage(&msg, NULL, 0, 0))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}

	//	popupDlg.DestroyWindow();
	//}

	return TRUE;
}



void CCSMServerSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{

	switch(nIDEvent)
	{
		case TIMER_MOVE_POPUPDIALOG:
			{

				if (TRUE == m_bIsPopupDialogUping)
				{
					if (m_iCurrentHeight < m_iHeightPopupDialog)
					{
						m_iCurrentHeight++;
						m_iStep--;
					}
				} 
				//else
				//{
				//	::OutputDebugStringA("down\n");
				//	if (m_iCurrentHeight > m_iHeightPopupDialog)
				//	{
				//		m_iCurrentHeight--;
				//		m_iStep++;
				//	}
				//}
				
				m_popupDialog.SetWindowPos(NULL, m_iXPopupDialog, m_iYPopupDialog + m_iStep, m_iWidthPopupDialog, m_iCurrentHeight, 0);


				//m_iYPopupDialog = m_iYPopupDialog - 1;
				//CString strText;

				//strText.Format(L"(x = %d, y = %d)\n", m_iXPopupDialog, m_iYPopupDialog + m_iStep);
				//::OutputDebugString(strText);
			}
	}

	CDialog::OnTimer(nIDEvent);
}

DWORD WINAPI CCSMServerSimulatorDlg::MovePopupDialogThreadFunction( PVOID pvParam )
{
	CCSMServerSimulatorDlg *pMainDlg = (CCSMServerSimulatorDlg*)pvParam;

	while(true)
	{
		if (TRUE == pMainDlg->m_bIsPopupDialogUping)
		{
			if (pMainDlg->m_iCurrentHeight < pMainDlg->m_iHeightPopupDialog)
			{
				pMainDlg->m_iCurrentHeight++;
				pMainDlg->m_iStep--;
			}
		}
		else
		{
			if (pMainDlg->m_iCurrentHeight > 0)
			{
				pMainDlg->m_iCurrentHeight--;
				pMainDlg->m_iStep++;
			}
		}

		pMainDlg->SetPopupDialogCoordinates();
		pMainDlg->m_popupDialog.SetWindowPos(NULL, pMainDlg->m_iXPopupDialog, pMainDlg->m_iYPopupDialog + pMainDlg->m_iStep, pMainDlg->m_iWidthPopupDialog, pMainDlg->m_iCurrentHeight, 0);
		Sleep(10);
	}
	
	return 0;
}

void CCSMServerSimulatorDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	//AdjustPopupDialogPosition();
	//int x = lpwndpos->x;
	//int y = lpwndpos->y;

	//if (lpwndpos->flags & SWP_NOMOVE)
	//{
	//	return;
	//}

	//if (-1 == lpwndpos->cx && -1 == lpwndpos->cy)
	//{
	//	return;
	//}

	//AdjustPopupDialogPosition();
	//CString strText;
	//strText.Format(L"(x = %d, y = %d)\n", lpwndpos->x, lpwndpos->y);
	//::OutputDebugString(strText);

	//int iNewXPopupDialog = x + lpwndpos->cx - m_iWidthPopupDialog;
	//int iNewYPopupDialog = y + lpwndpos->cy;

	//strText;
	//strText.Format(L"(x = %d, y = %d)\n", iNewXPopupDialog, iNewYPopupDialog);
	//::OutputDebugString(strText);

	//::OutputDebugString(L"Set window pos\n");
	//m_popupDialog.SetWindowPos(NULL, iNewXPopupDialog, iNewYPopupDialog, 0, 0, SWP_NOSIZE);
	//bool static flag = false;
	//if (false == flag)
	//{
	//	flag = TRUE;
	//	m_popupDialog.ShowWindow(SW_SHOW);
	//}
	//::OutputDebugStringA("move\n");
	//if (x != 0 && y != 0)
	//{
	//	CDialog::OnWindowPosChanging(lpwndpos);

	//	CString strText;
	//	strText.Format(L"(x = %d, y = %d)\n", lpwndpos->x, lpwndpos->y);
	//	::OutputDebugString(strText);

	//	m_popupDialog.SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
	//}


	//m_popupDialog.SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
}

void CCSMServerSimulatorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	//if (TRUE == bShow)
	//{
	//	bool static bFirst = true;

	//	if (true == bFirst)
	//	{
	//		bFirst = false;

	//		SetPopupDialogCoordinates();


	//		m_popupDialog.SetWindowPos(NULL, m_iXPopupDialog, m_iYPopupDialog, 0, 0, SWP_NOSIZE);

	//		m_popupDialog.ShowWindow(SW_SHOW);

	//		HANDLE hThread = ::CreateThread(NULL, 0, MovePopupDialogThreadFunction, this, 0, NULL);

	//		if (NULL != hThread) {
	//			::CloseHandle(hThread);
	//		}

	//		//SetTimer(TIMER_MOVE_POPUPDIALOG, 10, NULL);
	//	}
	//}
}

void CCSMServerSimulatorDlg::AdjustPopupDialogPosition()
{
	WINDOWPLACEMENT mainDialogPosition;
	GetWindowPlacement(&mainDialogPosition);

	int iNewXPopupDialog = mainDialogPosition.rcNormalPosition.right  - m_iWidthPopupDialog;
	int iNewYPopupDialog = mainDialogPosition.rcNormalPosition.bottom;

	m_popupDialog.SetWindowPos(NULL, iNewXPopupDialog, iNewYPopupDialog, 0, 0, SWP_NOSIZE);
}

void CCSMServerSimulatorDlg::OnBnClickedBtnDown()
{
	m_bIsPopupDialogUping = FALSE;
	if (FALSE == m_bIsPopupDialogUping)
	{
		::OutputDebugStringA("it works\n");
	}
}

void CCSMServerSimulatorDlg::OnBnClickedBtnUp()
{
	m_bIsPopupDialogUping = TRUE;
	if (TRUE == m_bIsPopupDialogUping)
	{
		::OutputDebugStringA("it works\n");
	}
}

void CCSMServerSimulatorDlg::SetPopupDialogCoordinates()
{
	WINDOWPLACEMENT mainDialogPosition;
	GetWindowPlacement(&mainDialogPosition);

	m_iXPopupDialog = mainDialogPosition.rcNormalPosition.right  - m_iWidthPopupDialog;
	m_iYPopupDialog = mainDialogPosition.rcNormalPosition.bottom;
}
