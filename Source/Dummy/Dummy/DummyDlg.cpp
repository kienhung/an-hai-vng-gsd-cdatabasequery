// DummyDlg.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "Dummy.h"
#include "DummyDlg.h"
#include "RegistryHelper.h"
#include "WinINET/HTTPRequester.h"
#include "WinINET/HTTPDownloader.h"
#include "BlackListReader.h"

#pragma warning (disable : 4996 )


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define		TIMER_PING_SERVER			100
#define		TIMER_UPDATE_BLACK_LIST		101


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


// CDummyDlg dialog




CDummyDlg::CDummyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDummyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsRegistered = FALSE;
	m_bIsVisibleDlg = FALSE;
}

void CDummyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER_REGISTER, m_webRegister);
}

BEGIN_MESSAGE_MAP(CDummyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TRAY_ICON_NOTIFY, OnTrayNotification)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(IDM_EXIT, &CDummyDlg::OnExit)
	ON_COMMAND(IDM_REGISTER_INFO, &CDummyDlg::OnRegisterInfo)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDummyDlg message handlers

BOOL CDummyDlg::OnInitDialog()
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

	// Set App startup with windows.
	CRegistryHelper registryHelper;
	registryHelper.SetStartUp();

	// test
	/*CRegistry reg(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));
	reg.SetValue(_T("Dummy"), "C:\\Dummy.exe")'

	reg.SetKey(HKEY_LOCAL_MACHINE, "");
	strPath[MAX_PATH] = {0};
	reg.ReadValue(_T("Dummy"), strPath, MAX_PATH);*/

	AddIconToSystemTray();
	SetTimer(TIMER_PING_SERVER, 60*1000, NULL);
	SetTimer(TIMER_UPDATE_BLACK_LIST, 3*60*1000, NULL);

	PostMessage(WM_CHECK_SHOW_REGISTER_INFO);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDummyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDummyDlg::OnPaint()
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
HCURSOR CDummyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CDummyDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_CHECK_SHOW_REGISTER_INFO)
	{
		CRegistryHelper registryHelper;
		m_bIsRegistered = registryHelper.CheckRegister();
		
		if (!m_bIsRegistered)
		{
			ShowRegisterInfo();
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDummyDlg::OnWindowPosChanging(WINDOWPOS *lpwndpos)
{
	if(!m_bIsVisibleDlg && lpwndpos->flags & SWP_SHOWWINDOW)
	{
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}


LRESULT CDummyDlg::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
	switch (lEvent ) 
	{
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
			{
				CMenu Menu;

				VERIFY(Menu.LoadMenu(IDR_TRAY_MENU));
				int iMenuID = 0;
				CMenu* pPopup = Menu.GetSubMenu(iMenuID);
				ASSERT(pPopup != NULL);

				POINT point;
				GetCursorPos(&point);
				SetForegroundWindow();

				pPopup->TrackPopupMenu(TPM_RIGHTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				ShowRegisterInfo();
				//PostMessage(WM_CHECK_SHOW_REGISTER_INFO);
			}
			break;
	}

	return 1;
}

void CDummyDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	RemoveIconFromSystemTray();
}

void CDummyDlg::AddIconToSystemTray()
{
	NOTIFYICONDATA NotifyIcon;

	memset(&NotifyIcon, 0, sizeof(NotifyIcon));
	NotifyIcon.cbSize = sizeof(NotifyIcon);
	NotifyIcon.hIcon = m_hIcon;
	NotifyIcon.hWnd	= m_hWnd;
	_tcscpy(NotifyIcon.szTip, _T("Dummy"));
	NotifyIcon.uCallbackMessage	= WM_TRAY_ICON_NOTIFY;
	NotifyIcon.uFlags	=	NIF_ICON | NIF_MESSAGE | NIF_TIP;
	NotifyIcon.uID		=	IDR_TRAY_MENU;
	Shell_NotifyIcon(NIM_ADD, &NotifyIcon);
}

void CDummyDlg::RemoveIconFromSystemTray()
{
	NOTIFYICONDATA NotifyIcon;

	memset(&NotifyIcon, 0, sizeof(NotifyIcon));
	NotifyIcon.cbSize	=	sizeof(NotifyIcon);
	NotifyIcon.hWnd	=	m_hWnd;
	NotifyIcon.uID		=	IDR_TRAY_MENU;
	Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);
}

void CDummyDlg::ShowRegisterInfo()
{
	m_webRegister.HideScrollBars();
	m_webRegister.Navigate(_T("file:///C:/Users/Administrator/Desktop/test.html"), NULL, NULL, NULL, NULL);
	m_bIsVisibleDlg = TRUE;
	ShowWindow(SW_SHOW);
}

void CDummyDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CDummyDlg::OnExit()
{
	// TODO: Add your command handler code here
	//PostMessage(WM_CLOSE);
	PostQuitMessage(0);
}

void CDummyDlg::OnRegisterInfo()
{
	// TODO: Add your command handler code here
	ShowRegisterInfo();
}

void CDummyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case TIMER_PING_SERVER:
			{
				::OutputDebugStringA("ping sever\n");

				PingServer();
			}
			break;

		case TIMER_UPDATE_BLACK_LIST:
			{
				::OutputDebugStringA("update black list\n");

				UpdateBlackList();

			}
			break;
	}
	CDialog::OnTimer(nIDEvent);
}




BEGIN_EVENTSINK_MAP(CDummyDlg, CDialog)
	ON_EVENT(CDummyDlg, IDC_EXPLORER_REGISTER, 250, CDummyDlg::BeforeNavigate2ExplorerRegister, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()

void CDummyDlg::BeforeNavigate2ExplorerRegister(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	// TODO: Add your message handler code here
	CString strURL(*URL);
	if(strURL.Find(_T("dummysuccess.com"), 0) >= 0)
	{
		CRegistryHelper registryHelper;
		registryHelper.UpdateRegistered(TRUE);
		AfxMessageBox(_T("Đăng ký thành công"));
		
	}
	else if(strURL.Find(_T("dummyclose.com"), 0) >= 0)
	{
		PostQuitMessage(0);
	}
}

BOOL CDummyDlg::UpdateBlackList()
{
	CBlackListReader blackListReader;
	CString cstrTempFilePath;

	if (FALSE == blackListReader.CreateTempFile(cstrTempFilePath))
	{
		return FALSE;
	}

	CHTTPDownloader httpDownloader;
	LPCTSTR strBlackListURL = L"http://csm.vng.com.vn/download/wblist.txt";

	if (FALSE == httpDownloader.Download(strBlackListURL, cstrTempFilePath))
	{
		return FALSE;
	}

	BOOL bBlackListReadingResult = blackListReader.Read(cstrTempFilePath);
	::DeleteFile(cstrTempFilePath);

	return bBlackListReadingResult;
}

BOOL CDummyDlg::PingServer()
{
	LPCTSTR strServerURL = L"http://localhost/Dummy/Master.asp";
	LPCTSTR strData = L"machineCode=vng4567";

	CHTTPRequester httpRequester;
	return httpRequester.PostRequest(strServerURL, strData);
}
