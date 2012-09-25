// CSMServerSimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSMServerSimulator.h"
#include "CSMServerSimulatorDlg.h"
#include "MyDefine.h"

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
	
	ON_BN_CLICKED(IDC_BTN_DOWN, &CCSMServerSimulatorDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_UP, &CCSMServerSimulatorDlg::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_KILLTHREAD, &CCSMServerSimulatorDlg::OnBnClickedBtnKillthread)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_NCRBUTTONDOWN()

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


	m_bIsPopupDialogExist = m_popupDialog.Create(CPopupDlg::IDD);

	if (TRUE == m_bIsPopupDialogExist)
	{
		RECT popupDialogWindowRect;
		m_popupDialog.GetClientRect(&popupDialogWindowRect);
	
		m_iWidthPopupDialog = popupDialogWindowRect.right - popupDialogWindowRect.left;
		m_iHeightPopupDialog = popupDialogWindowRect.bottom - popupDialogWindowRect.top;

		Initialize();

		m_bIsMovePopupDialogThreadRunning = TRUE;
		m_hMovePopupDialogThread = ::CreateThread(NULL, 0, MovePopupDialogThreadFunction, this, 0, NULL);
	}


	return TRUE;
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
}

DWORD WINAPI CCSMServerSimulatorDlg::MovePopupDialogThreadFunction( PVOID pvParam )
{
	CCSMServerSimulatorDlg *pMainDlg = (CCSMServerSimulatorDlg*)pvParam;


	while(TRUE == pMainDlg->m_bIsMovePopupDialogThreadRunning)
	{
		if (FALSE == pMainDlg->m_bIsMovePopupDialogThreadPausing)
		{
			if (TRUE == pMainDlg->m_bIsUp)
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
		}

		pMainDlg->SetPopupDialogCoordinates();
		Sleep(MOVE_POPUP_DIALOG_TIME);
	}

	return 0;
}

void CCSMServerSimulatorDlg::OnBnClickedBtnDown()
{
	m_bIsUp = FALSE;
}

void CCSMServerSimulatorDlg::OnBnClickedBtnUp()
{
	m_bIsUp = TRUE;
}

BOOL CCSMServerSimulatorDlg::SetPopupDialogCoordinates()
{
	WINDOWPLACEMENT mainDialogPosition;
	GetWindowPlacement(&mainDialogPosition);

	if (SW_SHOWNORMAL == mainDialogPosition.showCmd)
	{
		m_iXPopupDialog = mainDialogPosition.rcNormalPosition.right  - m_iWidthPopupDialog;
		m_iYPopupDialog = mainDialogPosition.rcNormalPosition.bottom;

	} 
	else if (SW_SHOWMAXIMIZED == mainDialogPosition.showCmd)
	{
		RECT rect;
		GetWindowRect(&rect);

		m_iXPopupDialog = rect.right  - m_iWidthPopupDialog;
		m_iYPopupDialog = rect.bottom;
	}

	int iCxBorder =	::GetSystemMetrics(SM_CXSIZEFRAME) + ::GetSystemMetrics(SM_CXBORDER); 
	
	if (TRUE == m_bIsPopupDialogExist)
	{
		m_popupDialog.SetWindowPos(NULL, m_iXPopupDialog - iCxBorder, m_iYPopupDialog + m_iStep, m_iWidthPopupDialog, m_iCurrentHeight, 0);
	}


	return TRUE;
}

void CCSMServerSimulatorDlg::OnBnClickedBtnKillthread()
{
	m_bIsMovePopupDialogThreadRunning = FALSE;
}

void CCSMServerSimulatorDlg::OnClose()
{
	m_bIsMovePopupDialogThreadRunning = FALSE;

	if (NULL != m_hMovePopupDialogThread)
	{
		//::WaitForSingleObject(m_hMovePopupDialogThread, INFINITE);
		::CloseHandle(m_hMovePopupDialogThread);
	}

	CDialog::OnClose();
}

void CCSMServerSimulatorDlg::OnSize(UINT nType, int cx, int cy)
{
	static BOOL bIsWindowMinimized = FALSE;

	if (SIZE_MINIMIZED == nType)
	{
		bIsWindowMinimized = TRUE;
		m_popupDialog.ShowWindow(SW_HIDE);

	}
	else if (SIZE_RESTORED == nType || SIZE_MAXIMIZED == nType)
	{
		if (TRUE == bIsWindowMinimized)
		{
			bIsWindowMinimized = FALSE;
			Initialize();
		}
	}
}

void CCSMServerSimulatorDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	m_bIsMovePopupDialogThreadPausing = TRUE;
	SetTimer(TIMER_CHECK_LEFT_MOUSE_UP, CHECK_MOUSE_UP_TIME, NULL);
	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CCSMServerSimulatorDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	m_bIsMovePopupDialogThreadPausing = TRUE;
	SetTimer(TIMER_CHECK_RIGHT_MOUSE_UP, CHECK_MOUSE_UP_TIME, NULL);
	CDialog::OnNcRButtonDown(nHitTest, point);
}

void CCSMServerSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{

	switch(nIDEvent)
	{
		case TIMER_CHECK_LEFT_MOUSE_UP:
			{
				if ((GetKeyState(VK_LBUTTON) & 0x80) == 0)
				{
					KillTimer(TIMER_CHECK_LEFT_MOUSE_UP);
					m_bIsMovePopupDialogThreadPausing = FALSE;;
				}
			}
			break;

		case  TIMER_CHECK_RIGHT_MOUSE_UP:
			{
				if ((GetKeyState(VK_RBUTTON) & 0x80) == 0)
				{
					KillTimer(TIMER_CHECK_RIGHT_MOUSE_UP);
					m_bIsMovePopupDialogThreadPausing = FALSE;
				}
			}
			break;

		case TIMER_SHOW_POPUP_DIALOG:
			{
				KillTimer(TIMER_SHOW_POPUP_DIALOG);

				if (TRUE == m_bIsPopupDialogExist)
				{
					m_popupDialog.ShowWindow(SW_SHOW);
				}

				m_bIsMovePopupDialogThreadPausing = FALSE;
			}

			break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CCSMServerSimulatorDlg::Initialize()
{
	m_bIsMovePopupDialogThreadPausing = TRUE;
	int iCyBorder =	::GetSystemMetrics(SM_CYSIZEFRAME) + + ::GetSystemMetrics(SM_CYBORDER); 

	m_iStep = -iCyBorder;
	m_iCurrentHeight = 0;

	m_bIsUp = TRUE;
	
	SetTimer(TIMER_SHOW_POPUP_DIALOG, SHOW_POPUP_DIALOAD_TIME, NULL);
}


